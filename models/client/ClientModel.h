/*
 * File: ClientModel.h
 * Created: 2019-12-2
 *
 * Copyright (c) shecks 2019 <shecks@gmail.com>
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

#ifndef _CLIENTMODEL_H
#define _CLIENTMODEL_H

#include <QObject>
#include <QStateMachine>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestNetworkManager;
class RestResponse;

class SocketNetworkManager;
class SocketResponse;

class RestResponseServerInfo;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ClientModel
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ClientModel : public QObject {
    typedef QObject _super;

    friend class ConnectionStateMachine;

    Q_OBJECT

public:
    enum ConnectionState {
        STATE_Error                 = -1,

        STATE_Disconnected          = 0,
        STATE_Connected             = 1
    };

    enum AuthenticationMode {
        AuthenticationMode_Token,
        AuthenticationMode_Email_Password,
        AuthenticationMode_Invalid
    };

    explicit ClientModel(const QString& host, int port = -1, bool isSecure = false, QObject* parent = nullptr);
    virtual ~ClientModel();

    void openConnection(const QString& authToken);
    void openConnection(const QString& email, const QString& password);

    void closeConnection();


signals:
    void _connectState_serverVersion();
    void _connectState_authenticationOptions();

public slots:

private slots:
    void _connectState_getServerVersion();
    void _connectState_getAuthenticationOptions();

public slots:
    void _onRestResponseReceived(const RestResponse& response);
    void _onSocketResponseReceived(const SocketResponse& response);

    void _onServerVersionReceived(const RestResponseServerInfo& response);
    //void _onAuthModVersionReceived(const A)
private:
    AuthenticationMode _authMode;

    QString _authEmail;
    QString _authPassword;
    QString _authToken;

    QStateMachine* _connectStateMachine;

    RestNetworkManager* _restManager;
    SocketNetworkManager* _socketManager;
};

#endif // _CLIENTMODEL_H
