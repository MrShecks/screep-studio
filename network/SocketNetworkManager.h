/*
 * File: SocketNetworkManager.h
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

#ifndef _SOCKETNETWORKMANAGER_H
#define _SOCKETNETWORKMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QWebSocket>
#include <QTimer>
#include <QMap>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _DBG_SHOW_SERVER_PONG       0
#define _DEB_SHOW_SERVER_RESPONSE   0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketResponse
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SocketResponse {
    friend class SocketNetworkManager;

public:
    virtual ~SocketResponse() {

    }

    const QString& channel() const              { return _channel; }
    const QString& stream() const               { return _stream; }
    const QJsonDocument& json() const           { return _json; }

    QString toString() const;

    bool commandMatches(const QString& channel, const QString& stream) const;
    bool channelMatches(const QString& channel) const;
    bool streamMatches(const QString& stream) const;

protected:
    SocketResponse(const QString& channel, const QString& stream, const QJsonDocument& json);

private:
    QString _channel;
    QString _stream;
    QJsonDocument _json;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketResponseError
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SocketResponseError : public SocketResponse {
    typedef SocketResponse _super;

    friend class SocketNetworkManager;

public:
    virtual ~SocketResponseError() {

    }

    const QString& errorMessage() const         { return _errorMessage; }

private:
    QString _errorMessage;

    SocketResponseError(const QString& channel, const QString& stream, const QString& errorMessage);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketCommandBuilder
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SocketCommandBuilder {

public:
    virtual ~SocketCommandBuilder();

    QString build() const;

    void addParam(const QString& value);
    void addParam(int value);

protected:
    SocketCommandBuilder(const QString& command);

private:
    QString _command;
    QStringList _params;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketNetworkManager
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SocketNetworkManager : public QObject {
    typedef QObject _super;

    Q_OBJECT

public:
    explicit SocketNetworkManager(QObject* parent = nullptr);
    virtual ~SocketNetworkManager();

    void openConnection(const QString& host, int port = -1, bool isSecure = false);
    void closeConnection();

    void sendCommand(const SocketCommandBuilder& command);
    void sendCommand(const QString& command, const QString& parameters = QString());

    void subscribe(const QString& channel, const QString objectName = QString());
    void unsubscribe(const QString& channel, const QString objectName = QString());

    void subscribeRoom(const QString& roomName, const QString& shardName = QString());
    void unsubscribeRoom(const QString& roomName, const QString& shardName = QString());

    bool isConnected() const                    { return _isConnected; }

signals:
    void connected();
    void disconnected();

    void responseReceived(const SocketResponse& response);
    void errorReceived(const SocketResponseError& response);

public slots:
    void ping();

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(const QString& message);

#if _DBG_SHOW_SERVER_PONG
    void onPongReceived(quint64 elapsedTime, const QByteArray& payload);
#endif // _DBG_SHOW_SERVER_PONG

private:
    typedef QMap<QString, int> TSubscriptionMap;

    QWebSocket _socket;
    bool _isConnected;

    TSubscriptionMap _subscriptions;
};

#endif // _SOCKETNETWORKMANAGER_H
