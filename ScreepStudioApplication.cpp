/*
 * File: ScreepStudioApplication.cpp
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

#include "ScreepStudioApplication.h"

#include "./models/server/ServerInfoModel.h"
#include "./models/user/UserInfoModel.h"
#include "./models/console/ConsoleModel.h"
#include "./models/room/RoomModel.h"

#include "./network/rest/RestRoomTerrain.h"
#include "./network/socket/SocketEventRoom.h"

#include "MainWindow.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define CONNECT_LIVE_SERVER     1
#define CONNECT_RIMMER_WORLD    0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString ScreepStudioApplication::COMPANY_NAME         = QStringLiteral("Mr Shecks Inc");
const QString ScreepStudioApplication::APPLICATION_NAME     = QStringLiteral("Screep Studio");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ScreepStudioApplication()
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ScreepStudioApplication::ScreepStudioApplication(int& argc, char** argv, int flags /* = ApplicationFlags */)
    : _super(argc, argv, flags),
      _prefs(COMPANY_NAME, APPLICATION_NAME),
      _networkModel(new NetworkModel(this)),
      _serverInfoModel(new ServerInfoModel(this)),
      _userInfoModel(new UserInfoModel(this)),
      _worldModel(new WorldModel(_networkModel, this)),
      _consoleModel(new ConsoleModel(this)),
      _mainWindow(new MainWindow()) {

    setApplicationName(APPLICATION_NAME);

    connect(_networkModel, &NetworkModel::connectionStateChanged, this, &ScreepStudioApplication::_onConnectionStateChanged);
    connect(_networkModel, &NetworkModel::serverInfoReceived, _serverInfoModel, &ServerInfoModel::refresh);
    connect(_networkModel, &NetworkModel::userInfoReceived, _userInfoModel, &UserInfoModel::refresh);
    connect(_networkModel, &NetworkModel::roomTerrainReceived, this, &ScreepStudioApplication::_onRoomTerrainReceived);
    connect(_networkModel, &NetworkModel::roomEventReceived, this, &ScreepStudioApplication::_onRoomEventReceived);

#if CONNECT_LIVE_SERVER
    qDebug() << "QSslSocket Build Version=" << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "SSL version found=" << QSslSocket::sslLibraryVersionNumber() << ", Library Path=" << QCoreApplication::libraryPaths();

    _networkModel->setAuthentication ("ea034548-7886-4a9a-86e4-74ed0a4ed473");
    _networkModel->openConnection("screeps.com", -1, true);
#else
    _networkModel->setAuthentication ("Shecks", "mysecretpassword");
#if CONNECT_RIMMER_WORLD
    _networkModel->openConnection("192.168.1.13", 21025, false);
#else
    _networkModel->openConnection("192.168.1.11", 21025, false);
#endif // CONNECT_RIMMER_WORLD
#endif // CONNECT_LIVE_SERVER

    _consoleModel->setModel(_networkModel);
}

ScreepStudioApplication::~ScreepStudioApplication() {

    _networkModel->closeConsole(_userInfoModel->id());
    delete _mainWindow;

    // FIXME: Remove these, there's no need to explicitly delete QObjects if they are parented

    delete _consoleModel;
    delete _worldModel;
    delete _userInfoModel;
    delete _serverInfoModel;
}

const QString& ScreepStudioApplication::userId() const {
    return _userInfoModel->id();
}

RoomModel::TSharedPtr ScreepStudioApplication::createRoomModel(const QString& roomName, const QString& shardName /* = QString() */) {
    const QString mapKey = roomMapKey(roomName, shardName);
    RoomModel::TSharedPtr roomModel = findRoomModel(mapKey);

    if(roomModel == nullptr) {
        roomModel = RoomModel::TSharedPtr::create(_networkModel, roomName, shardName);
        _roomModels.insert(mapKey, roomModel);
    }
#ifdef QT_DEBUG
    else {
        qDebug() << "Room with mapKey=" << mapKey << " already open!";
    }
#endif // QT_DEBUG

    return roomModel;
}

void ScreepStudioApplication::destroyRoomModel(const RoomModel::TSharedPtr roomModel) {
    Q_ASSERT(roomModel != nullptr);
    const QString mapKey = roomMapKey(roomModel->roomName(), roomModel->shardName());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ScreepStudioApplication::_onRoomTerrainReceived(const RestResponseRoomTerrain& response) {
    qDebug() << "Room=" << response.roomName() << ", Shard=" << response.shardName();

    RoomModel::TSharedPtr roomModel;

    if((roomModel = findRoomModel(response.roomName(), response.shardName())) != nullptr) {
        QMetaObject::invokeMethod(roomModel.data(), "_onRoomTerrainReceived", Q_ARG(const RestResponseRoomTerrain&, response));
    }
#ifdef QT_DEBUG
    else {
        qDebug() << "Room=" << response.roomName()
                 << ", Shard=" << response.shardName()
                 << ", not found in Room Model Map!";
    }
#endif // QT_DEBUG
}

void ScreepStudioApplication::_onRoomEventReceived(const SocketEventRoom& event) {
    RoomModel::TSharedPtr roomModel;

    if((roomModel = findRoomModel(event.roomName(), event.shardName())) != nullptr) {
        QMetaObject::invokeMethod(roomModel.data(), "_onRoomEventReceived", Q_ARG(const SocketEventRoom&, event));
    }
#ifdef QT_DEBUG
    else {
        qDebug() << "Room=" << event.roomName()
                 << ", Shard=" << event.shardName()
                 << ", not found in Room Model Map!";
    }
#endif // QT_DEBUG
}

#include "models/world/WorldModel.h"

void ScreepStudioApplication::_onConnectionStateChanged(NetworkModel::ConnectionState oldState, NetworkModel::ConnectionState newState) {
    qDebug() << "oldState=" << oldState << ", newState=" << newState;

    if(newState == NetworkModel::StateConnected) {
        qDebug() << "Connected!";
        _networkModel->openConsole(_userInfoModel->id());

        _mainWindow->show();

        _worldModel->open("shard3");

#if CONNECT_LIVE_SERVER
        _mainWindow->openRoom("W19S47", "shard2");
//        _mainWindow->openRoom("W31S32", "shard2");

//        _mainWindow->openRoom("E32N24", "shard3");
//        _mainWindow->openRoom("W21N18", "shard1");
#else

        _mainWindow->openRoom("W8N3");

        _mainWindow->openRoom("W7N4");               // Too-Angel Bot
        _mainWindow->openRoom("W8N4");               // Too-Angel Bot
        _mainWindow->openRoom("W7N3");               // Too-Angel Bot
        _mainWindow->openRoom("W9N5");               // Too-Angel Bot
        _mainWindow->openRoom("W9N2");               // Too-Angel Bot
        _mainWindow->openRoom("W8N7");               // Too-Angel Bot

        //_mainWindow->openRoom("W15N12");


//        _mainWindow->openRoom("W5N4");              // Has Invaders, Source Extractor and Source Keeper
//        _mainWindow->openRoom("W1N9");
//        _mainWindow->openRoom("W9N1");
//        _mainWindow->openRoom("W9N9");


//        _mainWindow->openRoom("W7N1");
#endif // CONNECT_LIVE_SERVER

        // storage.db['rooms.objects'].update({ _id: '1bc30772347c388' },{ $set: { level: 8 }})
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomModel::TSharedPtr ScreepStudioApplication::findRoomModel(const QString& roomName, const QString& shardName) const {
    return findRoomModel(roomMapKey(roomName, shardName));
}

RoomModel::TSharedPtr ScreepStudioApplication::findRoomModel(const QString& mapKey) const {
    TRoomModelMap::const_iterator it = _roomModels.find(mapKey);

    return it != _roomModels.constEnd() ? it.value() : nullptr;
}

QString ScreepStudioApplication::roomMapKey(const QString& roomName, const QString& shardName) const {
    return QString("{%1:%2}")
            .arg(shardName.isEmpty () ? "shard0" : shardName)
            .arg(roomName).toLower();
}
