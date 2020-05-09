/*
 * File: RestNetworkManager.h
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

#ifndef _RESTNETWORKMANAGER_H
#define _RESTNETWORKMANAGER_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtWebSockets>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrlQuery>
#include <QMap>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _DBG_SHOW_REST_REQUESTS     0
#define _DBG_SHOW_REST_RESOINSE     0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NetworkResponse
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NetworkResponse {
public:
    virtual ~NetworkResponse()                  { /* NOP */ }

    const QUrl& responseUrl() const             { return _responseUrl; }
    const QUrl& requestUrl() const              { return _requestUrl; }

    QString requestPath() const                 { return _requestUrl.path(); }

    bool containsPath(const QString& path) const;

    bool hasQueryItem(const QString& key) const;
    QString queryItemValue(const QString& key, const QString& defaultValue = QString()) const;

    bool hasHeader(const QString& key) const;
    QString header(const QString& key, const QString& defaultValue = QString()) const;

protected:
    NetworkResponse(QNetworkReply* reply);

private:
    typedef QMap<QString, QString> THeaderMap;

    QUrl _responseUrl;
    QUrl _requestUrl;

    THeaderMap _headers;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestResponse
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestResponse : public NetworkResponse {
    typedef NetworkResponse _super;

    friend class RestNetworkManager;

public:
    virtual ~RestResponse() {

    }

    bool isSuccess() const;
    QString errorMessage() const;

    QString toString() const;

protected:
    const QJsonDocument& body() const           { return _body; }

private:
    QJsonDocument _body;

    RestResponse(QNetworkReply* reply);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RESTRequestBuilder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RESTRequestBuilder : public QUrl {
    typedef QUrl _super;

public:
    virtual ~RESTRequestBuilder();

    QUrl build(const QUrl& baseUrl) const;
    QByteArray body() const;

    void setPath(const QString& path);

    void addQueryItem(const QString& key, int value);
    void addQueryItem(const QString& key, const QString& value);

    void addBodyItem(const QString& key, int value);
    void addBodyItem(const QString& key, const QString& value);

protected:
    RESTRequestBuilder(const QString& path = QString());

private:
    QString _path;
    QUrlQuery _query;
    QJsonObject _body;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestNetworkManager()
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestNetworkManager : public QObject {
    typedef QObject _super;

    Q_OBJECT

public:
    explicit RestNetworkManager(QObject* parent = nullptr);
    RestNetworkManager(const QString& host, int port = -1, bool isSecure = false, QObject* parent = nullptr);

    virtual ~RestNetworkManager();

    void setRequestHeader(const QString& key, const QString& value);
    QString getRequestHeader(const QString& key, const QString& defaultValue = QString()) const;

    void getRequest(const RESTRequestBuilder& requestBuilder);
    void postRequest(const RESTRequestBuilder& requestBuilder);

signals:
    void restResponseReceived(const RestResponse& response);

public slots:
    void openConnection(const QString& host, int port = -1, bool isSecure = false);
    void closeConnection();

    void ping();

private slots:
    void onRequestFinished(QNetworkReply* reply);

private:
    typedef QMap<QString, QString> THttpHeaderMap;

    QNetworkAccessManager _network;

    THttpHeaderMap _requestHeaders;
    QUrl _baseRestUrl;

    QNetworkRequest createRequest(const QUrl& url, bool isPost = false) const;
};

#endif // _RESTNETWORKMANAGER_H
