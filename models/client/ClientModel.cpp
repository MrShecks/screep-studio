/*
 * File: ClientModel.cpp
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

#include "ClientModel.h"
#include "network/RestNetworkManager.h"
#include "network/SocketNetworkManager.h"

#include "network/rest/RestServerInfo.h"
#include "network/rest/RestAuthentication.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ClientModel
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ClientModel::ClientModel(const QString& host, int port /* = -1 */, bool isSecure /* = false */, QObject* parent /* = nullptr */)
    : _super(parent),
      _authMode(AuthenticationMode_Invalid),
      _connectStateMachine(new QStateMachine(this)),
      _restManager(new RestNetworkManager(host, port, isSecure, this)),
      _socketManager(new SocketNetworkManager(host, port, isSecure, this)) {

    Q_CHECK_PTR(_restManager);
    Q_CHECK_PTR(_socketManager);
    Q_CHECK_PTR(_connectStateMachine);

    connect(_restManager, &RestNetworkManager::restResponseReceived, this, &ClientModel::_onRestResponseReceived);
    connect(_socketManager, &SocketNetworkManager::responseReceived, this, &ClientModel::_onSocketResponseReceived);

    //
    // Setup the connection state machine
    //

    QState* state1 = new QState();
    QState* state2 = new QState();
    QFinalState* state3 = new QFinalState();

    //
    // State 1
    // Get server version information (REST /api/version)
    //

    connect(state1, &QState::entered, this, &ClientModel::_connectState_getServerVersion);
    state1->addTransition(this, &ClientModel::_connectState_serverVersion, state2);

    //
    // State 2
    // Get server auth options (REST /api/authmod)
    //

    connect(state2, &QState::entered, this, &ClientModel::_connectState_getAuthenticationOptions);
    state2->addTransition(this, &ClientModel::_connectState_authenticationOptions, state3);

    _connectStateMachine->addState(state1);
    _connectStateMachine->addState(state2);
    _connectStateMachine->addState(state3);
    _connectStateMachine->setInitialState(state1);
}

ClientModel::~ClientModel() {

}

void ClientModel::openConnection(const QString& authToken) {
    Q_CHECK_PTR(_connectStateMachine);

    _authToken = authToken;
    _authMode = AuthenticationMode_Token;
    _connectStateMachine->start();
}

void ClientModel::openConnection(const QString& email, const QString& password) {
    Q_CHECK_PTR(_connectStateMachine);

    _authEmail = email;
    _authPassword = password;
    _authMode = AuthenticationMode_Email_Password;
    _connectStateMachine->start();
}

void ClientModel::closeConnection() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ClientModel::_connectState_getServerVersion() {
    Q_CHECK_PTR(_restManager);
    _restManager->getRequest(RestRequestServerInfo());
}

void ClientModel::_connectState_getAuthenticationOptions() {
    Q_CHECK_PTR(_restManager);
    _restManager->getRequest(RestAuthModVersion::Request());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ClientModel::_onRestResponseReceived(const RestResponse& response) {
    qDebug() << "ClientModel::_onRestResponseReceived(): Response=" << response.toString();

//    if(_connectStateMachine->isRunning()) {
//        if(response.containsPath(Screeps::PATH_SERVER_VERSION))
//            emit _connectState_serverVersion();
//    }

    if(response.containsPath(Screeps::PATH_SERVER_VERSION))
        _onServerVersionReceived(RestResponseServerInfo(response));
}

void ClientModel::_onSocketResponseReceived(const SocketResponse& response) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ClientModel::_onServerVersionReceived (const RestResponseServerInfo& response) {
    qDebug() << "_onServerVersionReceived(): Response=" << response.toString();
}


