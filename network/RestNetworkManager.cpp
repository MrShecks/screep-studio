/*
 * File: NetworkManager.cpp
 * Created: 2018-12-2
 *
 * Copyright (c) shecks 2018 <shecks@gmail.com>
 * All rights reserved.
 *
 * This file is part of %QT_PROJECT_NAME%.
 *
 * %QT_PROJECT_NAME% is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * %QT_PROJECT_NAME% is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with %QT_PROJECT_NAME%.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <QUrl>
#include <QNetworkReply>
#include <QJsonObject>

#include "RestNetworkManager.h"
#include "utils/JSONUtils.h"
#include "ScreepsApi.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NetworkResponse
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool NetworkResponse::containsPath(const QString& path) const {
    return requestPath().contains(path, Qt::CaseInsensitive);
}

bool NetworkResponse::hasQueryItem(const QString& key) const {
    const QUrlQuery requestQuery(requestUrl().query());

    return requestQuery.hasQueryItem (key);
}

QString NetworkResponse::queryItemValue(const QString& key, const QString& defaultValue /* = QString() */) const {
    const QUrlQuery requestQuery(requestUrl().query());

    return requestQuery.hasQueryItem(key) ? requestQuery.queryItemValue(key) : defaultValue;
}

bool NetworkResponse::hasHeader(const QString& key) const {
    return _headers.contains(key);
}

QString NetworkResponse::header(const QString& key, const QString& defaultValue /* = QString() */) const {
    return _headers.value(key, defaultValue);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NetworkResponse::NetworkResponse(QNetworkReply* reply) {
    Q_ASSERT(reply != nullptr);

    _responseUrl = reply->url();
    _requestUrl = reply->request().url();

    QList<QNetworkReply::RawHeaderPair> rawHeaders = reply->rawHeaderPairs();
    QList<QNetworkReply::RawHeaderPair>::const_iterator it = rawHeaders.constBegin();
    QList<QNetworkReply::RawHeaderPair>::const_iterator limit = rawHeaders.constEnd();

    for(; it != limit; ++it)
        _headers.insert(it->first, it->second);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RESTResponse
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestResponse::RestResponse(QNetworkReply* reply)
    : _super(reply),
      _body(QJsonDocument::fromJson(reply->readAll())) {

}

bool RestResponse::isSuccess() const {

    //
    // NOTE: The Screeps REST API uses an integer rather
    // than boolean for the "ok" call status
    //

    return JSONUtils::getInt (body().object(), "ok", 0) == 1;
}

QString RestResponse::errorMessage() const {
    return JSONUtils::getString(body().object(), "error");
}

QString RestResponse::toString() const {
    return _body.toJson();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RESTRequestBuilder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RESTRequestBuilder::~RESTRequestBuilder() {

}

QUrl RESTRequestBuilder::build(const QUrl& baseUrl) const {
    QUrl url(baseUrl);

    url.setPath(_path);
    url.setQuery(_query);

    return url;
}

QByteArray RESTRequestBuilder::body() const {
    return QJsonDocument(_body).toJson();
}

void RESTRequestBuilder::setPath(const QString& path) {
    _path = path;
}

void RESTRequestBuilder::addQueryItem(const QString& key, int value) {
    addQueryItem(key, QString::number(value));
}

void RESTRequestBuilder::addQueryItem(const QString& key, const QString& value) {
    _query.addQueryItem (key, value);
}

void RESTRequestBuilder::addBodyItem(const QString& key, int value) {
    addBodyItem(key, QString::number(value));
}

void RESTRequestBuilder::addBodyItem(const QString& key, const QString& value) {
    _body.insert(key, value);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RESTRequestBuilder::RESTRequestBuilder(const QString& path /* = QString() */)
    : _path(path) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestNetworkManager()
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestNetworkManager::RestNetworkManager(QObject* parent /* = nullptr */)
    : _super(parent) {

    connect(&_network, &QNetworkAccessManager::finished, this, &RestNetworkManager::onRequestFinished);
}

RestNetworkManager::~RestNetworkManager() {

}

void RestNetworkManager::setRequestHeader (const QString& key, const QString& value) {
    _requestHeaders.insert(key, value);
}

QString RestNetworkManager::getRequestHeader(const QString& key, const QString& defaultValue /* = QString() */) const {
    return _requestHeaders.value(key, defaultValue);
}

void RestNetworkManager::getRequest(const RESTRequestBuilder& requestBuilder) {
    QNetworkRequest request = createRequest(requestBuilder.build(_baseRestUrl));

#if _DBG_SHOW_REST_REQUESTS
    qInfo() << "[REST GET]" << request.url().toString();
#endif // _DBG_SHOW_REST_REQUESTS

    _network.get(request);
}

void RestNetworkManager::postRequest(const RESTRequestBuilder& requestBuilder) {
    QNetworkRequest request = createRequest(requestBuilder.build(_baseRestUrl), true);

#if _DBG_SHOW_REST_REQUESTS
    qInfo() << "[REST POST]" << requestBuilder.body ();
#endif // _DBG_SHOW_REST_REQUESTS

    _network.post(request, requestBuilder.body());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RestNetworkManager::openConnection(const QString& host, int port /* = -1 */, bool isSecure /* = false */) {
    _baseRestUrl.setHost(host);
    _baseRestUrl.setScheme(isSecure ? "https" : "http");
    _baseRestUrl.setPort(port);
}

void RestNetworkManager::closeConnection() {

}

void RestNetworkManager::ping() {

    //
    // A authorisation token expire after some time (60 seconds?) we need to keep
    // our stored token up to date. The HTTP server will return a new token in the
    // HTTP response header (X-Token) for any authenticated requests we make, however
    // if no request are made by the client our stored token will expire and any future
    // request will be rejected as un-authorised. To get around this we periodically
    // "ping" the REST "/api/auth/me" endpoint which returns information about the
    // currently authenticated user and also happens to return the X-Token header.
    //

    QUrl url(_baseRestUrl);

    url.setPath(Screeps::PATH_AUTH_ME);
    _network.get(createRequest(url));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RestNetworkManager::onRequestFinished(QNetworkReply* reply) {
#if _DBG_SHOW_REST_RESOINSE
    qInfo() << "[REST RESPONSE]" << reply->error() << ", " << reply->request().url().toString();
#endif // _DBG_SHOW_REST_RESOINSE

    if(reply->error() == QNetworkReply::NoError) {
        emit restResponseReceived(RestResponse(reply));
    } else {

        //
        // FIXME: Need to propagate HTTP errors
        //

        qCritical() << "********************************************************************************\n"
                 << "*** HTTP ERROR\n"
                 << "*** Request=" << reply->request().url() << "\n"
                 << "*** Error=" << reply->error() << "-" << reply->errorString() << "\n"
                 << "*** Body=" << reply->readAll() << "\n"
                 << "********************************************************************************";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QNetworkRequest RestNetworkManager::createRequest(const QUrl& url, bool isPost /* = false */ ) const {
    THttpHeaderMap::const_iterator it = _requestHeaders.constBegin();
    THttpHeaderMap::const_iterator limit = _requestHeaders.constEnd();
    QNetworkRequest request(url);

    for(; it != limit; ++it)
        request.setRawHeader(it.key().toLatin1(), it.value().toLatin1());

    if(isPost)
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    return request;
}
