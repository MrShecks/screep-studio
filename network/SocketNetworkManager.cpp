/*
 * File: SocketNetworkManager.cpp
 * Created: 2018-12-6
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

#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonArray>

#include "SocketNetworkManager.h"
#include "ScreepsApi.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketResponse
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QString SocketResponse::toString() const {
    return QString("Channel=%1\nStream=%2\nJSON=%3")
            .arg(_channel)
            .arg(_stream)
            .arg(_json.toJson(QJsonDocument::Compact).data());
}

bool SocketResponse::commandMatches(const QString& channel, const QString& stream) const {
    return channelMatches(channel) && streamMatches(stream);
}

bool SocketResponse::channelMatches(const QString& channel) const {
    return _channel.compare(channel, Qt::CaseInsensitive) == 0;
}

bool SocketResponse::streamMatches(const QString& stream) const {
    return _stream.compare(stream, Qt::CaseInsensitive) == 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SocketResponse::SocketResponse(const QString& channel, const QString& stream, const QJsonDocument& json)
    :  _channel(channel),
      _stream(stream),
      _json(json) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketResponseError
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SocketResponseError::SocketResponseError(const QString& channel, const QString& stream, const QString& errorMessage)
    : _super(channel, stream, QJsonDocument()),
      _errorMessage(errorMessage) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketCommandBuilder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SocketCommandBuilder::~SocketCommandBuilder() {

}

QString SocketCommandBuilder::build() const {
    return QString("%1 %2").arg(_command).arg(_params.join (" "));
}

void SocketCommandBuilder::addParam(const QString& value) {
    _params.append(value);
}

void SocketCommandBuilder::addParam(int value) {
    _params.append(QString::number(value));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SocketCommandBuilder::SocketCommandBuilder(const QString& command)
    : _command(command) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketNetworkManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SocketNetworkManager::SocketNetworkManager(QObject* parent /* = nullptr */)
    : _super(parent),
      _isConnected(false) {

    connect(&_socket, &QWebSocket::connected, this, &SocketNetworkManager::connected);
    connect(&_socket, &QWebSocket::disconnected, this, &SocketNetworkManager::disconnected);

    connect(&_socket, &QWebSocket::connected, this, &SocketNetworkManager::onConnected);
    connect(&_socket, &QWebSocket::disconnected, this, &SocketNetworkManager::onDisconnected);
    connect(&_socket, &QWebSocket::textMessageReceived, this, &SocketNetworkManager::onTextMessageReceived);
#if _DBG_SHOW_SERVER_PONG
    connect(&_socket, &QWebSocket::pong, this, &SocketNetworkManager::onPongReceived);
#endif // _DBG_SHOW_SERVER_PONG
}

SocketNetworkManager::~SocketNetworkManager() {
    // TODO: Unsubscribe from all subscribed channels
#ifdef QT_DEBUG
    TSubscriptionMap::const_iterator it = _subscriptions.constBegin ();
    TSubscriptionMap::const_iterator limit = _subscriptions.constEnd();

    for(; it != limit; ++it) {
        qDebug() << "Subscription=" << it.key() << "RefCount=" << it.value();
    }

#endif // QT_DEBUG
}

void SocketNetworkManager::openConnection(const QString& host, int port /* = -1 */, bool isSecure /* = false */) {
    if(!_isConnected) {
        QUrl url;

        url.setHost(host);
        url.setScheme(isSecure ? "wss" : "ws");
        url.setPort(port);
        url.setPath (Screeps::WEBSOCKET_ENDPOINT);

        qDebug() << "Attempting to connect to: " << url.toString();

        _socket.open(url);
    }
}

void SocketNetworkManager::closeConnection() {
    if(_isConnected) {
        _socket.close();
    }
}

// FIXME: Deprecate!!!
void SocketNetworkManager::sendCommand(const SocketCommandBuilder& command) {
    sendCommand(command.build());
}

void SocketNetworkManager::sendCommand(const QString& command, const QString& parameters /* = QString() */) {
    const QString message = parameters.isEmpty() ? command : QString("%1 %2").arg(command).arg(parameters);

#ifdef QT_DEBUG
    qDebug() << "Message=" << message;
#endif // QT_DEBUG

    _socket.sendTextMessage(message);

}

void SocketNetworkManager::subscribe(const QString& channel, const QString objectName /* = QString() */) {
    const QString streamName = objectName.isEmpty() ? channel : QString("%1:%2").arg(channel).arg(objectName);
    TSubscriptionMap::iterator it;

    // We only manage a single subscription for each unique stream, so if
    // there's already one open we just increment the refercence counter.

    if((it = _subscriptions.find(streamName)) != _subscriptions.end())
        it.value()++;
    else {
        sendCommand("subscribe", streamName);
        _subscriptions.insert(streamName, 1);
    }
}

void SocketNetworkManager::unsubscribe(const QString& channel, const QString objectName /* = QString() */) {
    const QString streamName = objectName.isEmpty()  ? channel : QString("%1:%2").arg(channel).arg(objectName);
    TSubscriptionMap::iterator it;

    if((it = _subscriptions.find(streamName)) != _subscriptions.end()) {
        if(--it.value() == 0) {
            sendCommand("unsubscribe", streamName);
            _subscriptions.erase (it);
        }
    }
#ifdef QT_DEBUG
    else {
        qDebug() << "Attempt to unsubscribe from unknown stream: " << streamName;
    }
#endif // QT_DEBUG
}

void SocketNetworkManager::subscribeRoom(const QString& roomName, const QString& shardName /* = QString() */) {
    const QString objectName = shardName.isEmpty() ? roomName : QString("%1/%2").arg(shardName).arg(roomName);

    subscribe(Screeps::CHANNEL_ROOM, objectName);
}

void SocketNetworkManager::unsubscribeRoom(const QString& roomName, const QString& shardName /* = QString() */) {
    const QString objectName = shardName.isEmpty() ? roomName : QString("%1/%2").arg(shardName).arg(roomName);

    unsubscribe (Screeps::CHANNEL_ROOM, objectName);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SocketNetworkManager::ping() {
    if(_isConnected) {
        _socket.ping();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SocketNetworkManager::onConnected() {
    _isConnected = true;

    // TODO: Resubscribe to any subscribed channel
    // TODO: Send any missed commands
}

void SocketNetworkManager::onDisconnected() {
    _isConnected = false;
}

void SocketNetworkManager::onTextMessageReceived(const QString& message) {
    static const QRegularExpression REGEX_STREAM_RESPONSE("^\\[\"(?<channel>\\w+):(?<stream>[\\w\\/]+)\",(?<json>{.+})\\]$");
    static const QRegularExpression REGEX_STREAM_ERROR("^\\[\"err@(?<channel>\\w+):(?<stream>[\\w\\/]+)\",\"(?<error>.+)\"\\]$");
    static const QRegularExpression REGEX_COMMAND_RESPONSE("^(?<command>\\w+)\\s?(?<params>.+)?");
    QRegularExpressionMatch match;

    // ^\["(?<channel>\w+):(?<stream>[\w\/]+)",(?<json>{.+})\]$"
#if _DEB_SHOW_SERVER_RESPONSE
    qDebug().noquote () << "Message=" << message;
#endif // _DEB_SHOW_SERVER_RESPONSE

    if((match = REGEX_STREAM_RESPONSE.match(message)).hasMatch()) {
        const QString channel = match.captured("channel");
        const QString stream = match.captured("stream");

        QJsonParseError jsonError;
        QJsonDocument json = QJsonDocument::fromJson(match.captured("json").toUtf8(), &jsonError);          // FIXME: Should check for JSON parse errors!

        emit responseReceived(SocketResponse(channel, stream, json));

    } else if((match = REGEX_STREAM_ERROR.match(message)).hasMatch()) {
#ifdef QT_DEBUG
        qDebug() << "Stream Error: "
                 << "Channel=" << match.captured("channel")
                 << ", Stream=" << match.captured("stream")
                 << ", Error=" << match.captured ("error");
#endif // QT_DEBUG

        emit errorReceived(SocketResponseError(match.captured("channel"), match.captured("stream"), match.captured ("error")));

    } else if((match = REGEX_COMMAND_RESPONSE.match(message)).hasMatch()) {
        const QString command = match.captured("command");
        const QJsonArray params = QJsonArray::fromStringList(match.captured("params").split(QChar::Space));

        emit responseReceived(SocketResponse("system", command, QJsonDocument(params)));
    }
#ifdef QT_DEBUG
    else {

        qDebug() << "Unrecognised socket response format!";
        qDebug() << "*** Msg=" << message;
    }
#endif // QT_DEBUG

}

#if _DBG_SHOW_SERVER_PONG
void SocketNetworkManager::onPongReceived(quint64 elapsedTime, const QByteArray& payload) {
    qDebug() << "WebsocketManager::onPongReceived(): Elapsed Time:" << elapsedTime << ", Payload=" << payload;
}
#endif // _DBG_SHOW_SERVER_PONG
