/*
 * File: NetworkModel.cpp
 * Created: 2018-12-9
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

#include "NetworkModel.h"
#include "ScreepsApi.h"

#include "../network/rest/RestServerInfo.h"
#include "../network/rest/RestAuthentication.h"
#include "../network/rest/RestUserInfo.h"
#include "../network/rest/GameInfo.h"
#include "../network/rest/RestRoomTerrain.h"
#include "../network/rest/RestConsoleCommand.h"

#include "../network/socket/SocketCommandAuth.h"
#include "../network/socket/SocketCommandSubscribe.h"

#include "../network/socket/SocketEventUser.h"
#include "../network/socket/SocketEventRoom.h"
#include "../network/socket/SocketEventConsole.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NetworkModel
// The network model consolidates the network IO for both the REST and Websockets APIs. It provides a single
// interface for submitting network requests and propagating results (via signals) to the various application
// data models.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NetworkModel::NetworkModel(QObject *parent)
    : _super(parent),
      _restNetworkManager(this),
      _socketNetworkManager(this),
      _connectionState(StateDisconnected),
      _authenticationType(AuthenticationType_Unknown) {

    _pingTimer.setInterval(PING_TIMER_INTERVAL);

    connect(&_pingTimer, &QTimer::timeout, &_socketNetworkManager, &SocketNetworkManager::ping);
    connect(&_pingTimer, &QTimer::timeout, &_restNetworkManager, &RestNetworkManager::ping);

    connect(&_socketNetworkManager, &SocketNetworkManager::connected, this, &NetworkModel::_onSocketConnected);
    connect(&_socketNetworkManager, &SocketNetworkManager::disconnected, this, &NetworkModel::_onSocketDisconnected);
    connect(&_socketNetworkManager, &SocketNetworkManager::responseReceived, this, &NetworkModel::_onSocketResponseReceived);

    connect(&_restNetworkManager, &RestNetworkManager::restResponseReceived, this, &NetworkModel::_onRestResponseReceived);
}

NetworkModel::~NetworkModel() {

}

void NetworkModel::setAuthentication(const QString& authToken) {
    setAuthToken (authToken);
    _authenticationType = AuthenticationType_Token;
}

void NetworkModel::setAuthentication(const QString& userName, const QString& password) {
    _authUserName = userName;
    _authPassword = password;
    _authenticationType = AuthenticationType_Password;
}

bool NetworkModel::registerUser(const QString& userName, const QString& password, const QString& email /* = "" */) {
    Q_ASSERT(_connectionState == StateConnected);
    bool result = false;

    if(_connectionState == StateConnected) {
        _restNetworkManager.postRequest(RestPostRegisterUser(userName, password, email));
        result = true;
    }

    return result;
}

bool NetworkModel::openConnection(const QString& host, int port /* = -1 */, bool isSecure /* = false */) {
    bool result = false;

    if(_connectionState != StateConnected) {
        _connectionState = StateDisconnected;
        _restNetworkManager.openConnection(host, port, isSecure);
        _socketNetworkManager.openConnection(host, port, isSecure);
        result = true;
    }

    return result;
}

void NetworkModel::closeConnection() {
    _restNetworkManager.closeConnection();
    _socketNetworkManager.closeConnection();
    _connectionState = StateDisconnected;
}

void NetworkModel::openConsole(const QString& userId) {
    Q_ASSERT(_connectionState == StateConnected);

    if(_connectionState == StateConnected) {
        _socketNetworkManager.subscribe ("user", QString("%1/console").arg(userId));
    }
}

void NetworkModel::closeConsole(const QString& userId) {
    Q_ASSERT(_connectionState == StateConnected);

    if(_connectionState == StateConnected) {
        _socketNetworkManager.unsubscribe ("user", QString("%1/console").arg(userId));
    }
}

void NetworkModel::openRoom(const QString& roomName, const QString& shardName) {
    Q_ASSERT(_connectionState == StateConnected);

    if(_connectionState == StateConnected) {
        _socketNetworkManager.subscribeRoom(roomName, shardName);
    }
}

void NetworkModel::closeRoom(const QString& roomName, const QString& shardName) {
    Q_ASSERT(_connectionState == StateConnected);

    if(_connectionState == StateConnected) {
        _socketNetworkManager.unsubscribeRoom(roomName, shardName);
    }
}

bool NetworkModel::getWorldSize(const QString &shardName /* = QString() */) {
    Q_ASSERT(_connectionState == StateConnected);
    bool result = false;

    if(_connectionState == StateConnected) {
        _restNetworkManager.getRequest(WorldSizeRequest(shardName));
        result = true;
    }

    return result;
}

bool NetworkModel::getRoomTerrain(const QString& roomName, const QString& shardName /* = QString() */) {
    Q_ASSERT(_connectionState == StateConnected);
    bool result = false;

    if(_connectionState == StateConnected) {
        _restNetworkManager.getRequest(RestRequestRoomTerrain(roomName, shardName));
        result = true;
    }

    return result;
}

bool NetworkModel::sendConsoleCommand(const QString& expression, const QString& shardName /* = QString() */) {
    Q_ASSERT(_connectionState == StateConnected);
    bool result = false;

    if(_connectionState == StateConnected) {
        _restNetworkManager.postRequest(RestPostConsoleCommand(expression, shardName));
        result = true;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void NetworkModel::_onSocketConnected() {
    Q_ASSERT_X(_connectionState == StateDisconnected, "NetworkModel::_onSockeConnected()", "Unexpected connection state.");
    changeConnectionState(StateSocketConnected);
}

void NetworkModel::_onSocketDisconnected() {
    Q_ASSERT_X(_connectionState >= StateSocketConnected, "NetworkModel::_onSockeConnected()", "Unexpected connection state.");
    changeConnectionState(StateDisconnected);
}

void NetworkModel::_onSocketResponseReceived(const SocketResponse& response) {
    if(response.commandMatches("system", "auth")) {
        changeConnectionState(StateSocketAuthenticated);
    } else if(response.channelMatches("user")) {
        onEventUser(response);
    } else if(response.channelMatches("room")) {
        onEventRoom(response);
    }
}

void NetworkModel::_onRestResponseReceived(const RestResponse& response) {
#if _DEBUG_REST_RESPONSES
    qDebug() << "REST Response: " << response.toString();
#endif // _DEBUG_REST_RESPONSES
    //
    // The Screeps server will include an updated authentication token
    // in the response headers from time to time. When this happens we
    // need to update our stored token to be used in future HTTP requests.
    //

    if(response.isSuccess() && response.hasHeader(Screeps::HTTP_HEADER_TOKEN)) {
        const QString token = response.header(Screeps::HTTP_HEADER_TOKEN);

        if(authToken().compare(token) != 0) {
            setAuthToken(response.header(Screeps::HTTP_HEADER_TOKEN));
            qDebug() << "New Auth Token: " << token;
        }
    }

    if(response.containsPath(Screeps::PATH_SERVER_VERSION)) {
        emit serverInfoReceived (RestResponseServerInfo(response));
        changeConnectionState(StateRestConnected);

    } else if(response.containsPath(Screeps::PATH_AUTH_STEAM_TOKEN)) {
        qDebug() << "Response=" << response.toString();

    } else if(response.containsPath(Screeps::PATH_AUTH_SIGNIN)) {
        const RestResponseUserSignin signinResponse(response);

        setAuthToken(signinResponse.token());

        if(_connectionState != StateConnected)
            changeConnectionState(StateRestAuthenticated);

    } else if(response.containsPath(Screeps::PATH_AUTH_ME)) {
        emit userInfoReceived(RestResponseUserInfo(response));

        if(_connectionState != StateConnected)
            changeConnectionState(StateConnected);

    } else if(response.containsPath(Screeps::PATH_GAME_ROOMTERRAIN)) {
        emit roomTerrainReceived(RestResponseRoomTerrain(response));

    } else if(response.containsPath(Screeps::PATH_GAME_WORLDSIZE)) {
        emit worldSizeReceived(WorldSizeResponse(response));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QString NetworkModel::authToken() const {
    return _restNetworkManager.getRequestHeader(Screeps::HTTP_HEADER_TOKEN);
}

void NetworkModel::setAuthToken(const QString& authToken) {
    _restNetworkManager.setRequestHeader(Screeps::HTTP_HEADER_TOKEN, authToken);
    _restNetworkManager.setRequestHeader(Screeps::HTTP_HEADER_USERNAME, authToken);
}

void NetworkModel::onEventUser (SocketEventUser event) {
#if _DEBUG_USER_EVENTS
    qDebug() << "UserId=" << event.userId() << "\n"
             << "ObjectId=" << event.objectId() << "\n"
             << "Data=" << event.toString();
#endif // _DEBUG_USER_EVENTS

    if(event.objectIdMatches("console"))
        emit consoleEventReceived(SocketEventConsole(event));
}

void NetworkModel::onEventRoom(SocketEventRoom event) {
#if _DEBUG_ROOM_EVENTS
    qDebug() << "Shard=" << event.shardName() << "\n"
             << "Room=" << event.roomName() << "\n"
             << "JSON=" << event.toString();
#endif // _DEBUG_ROOM_EVENTS

    emit roomEventReceived(event);
}

void NetworkModel::changeConnectionState(ConnectionState newState) {
    ConnectionState oldState = _connectionState;

    _connectionState = newState;
    emit connectionStateChanged (oldState, newState);

    switch(newState) {
        case StateSocketConnected:      _restNetworkManager.getRequest(RestRequestServerInfo());                                    break;

        case StateRestConnected: {
            switch (_authenticationType) {
                case AuthenticationType_Token: {
                    _socketNetworkManager.sendCommand(SocketCommandAuth(authToken()));
                }
                break;

                case AuthenticationType_Ticket: {
                    _restNetworkManager.postRequest(RestRequestTicketSignin(_authTicket, false));
                }
                break;

                case AuthenticationType_Password: {
                    _restNetworkManager.postRequest(RestRequestUserSignin(_authUserName, _authPassword));
                }
                break;

                default: {
#ifdef QT_DEBUG
                    qDebug() << "Invalid Authentication Type!";
#endif // QT_DEBUG
                }
                break;
            }
        }
        break;

        case StateRestAuthenticated:    _socketNetworkManager.sendCommand(SocketCommandAuth(authToken()));                          break;
        case StateSocketAuthenticated:  _restNetworkManager.getRequest(RestRequestUserInfo());                                      break;

        case StateConnected: {
            _pingTimer.start();
            emit connected();
        }
        break;

        case StateDisconnected: {
            _pingTimer.stop();
            emit disconnected();
        }
        break;

        default: {

        }
        break;
    }
}
