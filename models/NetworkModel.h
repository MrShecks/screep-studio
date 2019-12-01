/*
 * File: NetworkModel.h
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

#ifndef _NETWORKMODEL_H
#define _NETWORKMODEL_H

#include <QObject>
#include <QTimer>

#include "network/RestNetworkManager.h"
#include "network/SocketNetworkManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Server Connection Flow Ideas
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Perhaps use a wizerd like flow for sign in
//
// 1) User selects or enters server host name and port (defailt port to 21025)
// 2) Clicking next should perform the following
// 2.1) Get server version information (basically checking if the server host is valid and listening)
// 2.2) Check if the screepsmod-auth modification is enabled (http://<host>:<port>/api/authmod)
// 3) Ask the user to select an authentication method based on the results
//      a) Steam token (if screepsmod-auth is not available)
//      b) Username/password (if screepsmod-auth is avaiable)
//      c) GitHub username/password (if screepsmod-auth is available and GitHub login == True)
//
// Note: If the user chooses to login using screepsmod-auth and registration is enabled (allowRegistration == True)
// then we should give them the option to register a new username/password
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _DEBUG_NETWORK_MODEL            1
#define _DEBUG_REST_RESPONSES           _DEBUG_NETWORK_MODEL && 0
#define _DEBUG_USER_EVENTS              _DEBUG_NETWORK_MODEL && 0
#define _DEBUG_ROOM_EVENTS              _DEBUG_NETWORK_MODEL && 0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestResponseServerInfo;
class RestResponseUserInfo;
class RestResponseRoomTerrain;

class WorldSizeResponse;

class SocketEventUser;
class SocketEventRoom;
class SocketEventConsole;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NetworkModel
// The network model consolidates the network IO for both the REST and Websockets APIs. It provides a single
// interface for submitting network requests and propagating results (via signals) to the various application
// data models.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NetworkModel : public QObject {
    typedef QObject _super;

    Q_OBJECT

    static const int PING_TIMER_INTERVAL    = 1000 * 30;

public:
    enum AuthenticationType {
        AuthenticationType_Unknown          = -1,

        AuthenticationType_Password,
        AuthenticationType_Token,
        AuthenticationType_Ticket
    };

    enum ConnectionState {
        StateError                          = -1,
        StateDisconnected                   =  0,
        StateSocketConnected                =  1,
        StateRestConnected                  =  2,
        StateRestAuthenticated              =  3,
        StateSocketAuthenticated            =  4,
        StateConnected                      =  5
    };

    Q_ENUM(ConnectionState);

    explicit NetworkModel(QObject* parent = nullptr);
    virtual ~NetworkModel();

    void setAuthentication(const QString& authToken);
    void setAuthentication(const QString& userName, const QString& password);

    bool registerUser(const QString& userName, const QString& password, const QString& email = "");

    bool openConnection(const QString& host, int port = -1, bool isSecure = false);
    void closeConnection();

    void openConsole(const QString& userId);
    void closeConsole(const QString& userId);

    void openRoom(const QString& roomName, const QString& shardName);
    void closeRoom(const QString& roomName, const QString& shardName);

    bool getWorldSize(const QString& shardName = QString());
    bool getRoomTerrain(const QString& roomName, const QString& shardName = QString());

    bool sendConsoleCommand(const QString& expression, const QString& shardName = QString());

signals:
    void serverInfoReceived(const RestResponseServerInfo& response);
    void userInfoReceived(const RestResponseUserInfo& response);

    void worldSizeReceived(const WorldSizeResponse& response);
    void roomTerrainReceived(const RestResponseRoomTerrain& response);

    void consoleEventReceived(const SocketEventConsole& event);
    void roomEventReceived(const SocketEventRoom& event);

    void connectionStateChanged(ConnectionState oldState, ConnectionState newState);

    void connected();
    void disconnected();

private slots:
    void _onSocketConnected();
    void _onSocketDisconnected();
    void _onSocketResponseReceived(const SocketResponse& response);

    void _onRestResponseReceived(const RestResponse& response);

private:
    RestNetworkManager _restNetworkManager;
    SocketNetworkManager _socketNetworkManager;
    QTimer _pingTimer;

    ConnectionState _connectionState;
    AuthenticationType _authenticationType;

    QString _authUserName;
    QString _authPassword;
    QString _authTicket;

    QString authToken() const;
    void setAuthToken(const QString& authToken);

    void onEventUser(SocketEventUser event);
    void onEventRoom(SocketEventRoom event);

    void changeConnectionState(ConnectionState newState);
};

#endif // NETWORKMODEL_H
