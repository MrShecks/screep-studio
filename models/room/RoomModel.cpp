/*
 * File: RoomModel.cpp
 * Created: 2018-12-1
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

#include "RoomModel.h"
#include "../../network/rest/RestRoomTerrain.h"
#include "../../network/socket/SocketEventRoom.h"

#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if _DEBUG_LOAD_MOCK_ENTITIES
#include <QDir>
#endif // _DEBUG_LOAD_MOCK_ENTITIES

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomModel()
// Complete representation of a single world room
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomModel::RoomModel(NetworkModel* networkModel, const QString& roomName, const QString& shardName, QObject* parent /* = nullptr */)
    : _super(parent),
      _networkModel(networkModel),
      _roomName(roomName),
      _shardName(shardName),
      _stateMachineOpen(new StateMachineOpen(this)),
      _isOpen(false) {

    qDebug() << "Created: Obj=" << this;

    connect(&_entityModel, &RoomEntityModel::roomEntityAdded, this, &RoomModel::roomEntityAdded);
    connect(&_entityModel, &RoomEntityModel::roomEntityUpdated, this, &RoomModel::roomEntityUpdated);
    connect(&_entityModel, &RoomEntityModel::roomEntityRemoved, this, &RoomModel::roomEntityRemoved);
}

RoomModel::~RoomModel() {
    qDebug() << "Destroyed: Obj=" << this;

    close();
}

void RoomModel::open() {
    _stateMachineOpen->start();
}

void RoomModel::close() {
    if(_isOpen) {
        _networkModel->closeRoom(_roomName, _shardName);
        _isOpen = false;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomModel::_refreshTerrain() {
    Q_ASSERT(!_networkModel.isNull());

    _networkModel->getRoomTerrain(_roomName, _shardName);
}

void RoomModel::_refreshEntities() {
    Q_ASSERT(!_networkModel.isNull());

    _networkModel->openRoom(_roomName, _shardName);
}

void RoomModel::_onRoomTerrainReceived(const RestResponseRoomTerrain& response) {
    Q_ASSERT(_roomName.compare(response.room().name()) == 0);

    _id = response.room().id();
    _terrainModel.setTerrain(response.room());

    emit roomTerrainReceived();
}

void RoomModel::_onRoomEventReceived(const SocketEventRoom& event) {

    if(_stateMachineOpen->isRunning ()) {
        _entityModel.beginRecover();
    }

    for(const SocketEventRoom::RoomEntity& eventEntity : event.entities()) {
        const QString& id = eventEntity.id();
        const QJsonObject& json = eventEntity.json();

        if(_entityModel.exists(id)) {
            if(eventEntity.isRemoved()) {
                _entityModel.removeEntity(id);

            } else {
#if _DEBUG_LOAD_MOCK_ENTITIES
                QJsonObject mockJson = loadMockEntity(id);
                _entityModel.updateEntity(id, mockJson.isEmpty() ? json : mockJson, event.gameTime());
#else
                _entityModel.updateEntity(id, json, event.gameTime());
#endif // _DEBUG_LOAD_MOCK_ENTITIES
            }

        } else {
#if _DEBUG_LOAD_MOCK_ENTITIES
            QJsonObject mockJson = loadMockEntity(id);
            _entityModel.addEntity (id, mockJson.isEmpty() ? json : mockJson);
#else
            _entityModel.addEntity (id, json);

#endif // _DEBUG_LOAD_MOCK_ENTITIES
        }
    }

    if(_stateMachineOpen->isRunning ()) {
        // Only emit this signal for the initial event stream
        // recover during the room open state sequence

        emit roomEntitiesReceived();
        _entityModel.endRecover();
        _isOpen = true;
    }
}

#if _DEBUG_LOAD_MOCK_ENTITIES
QJsonObject RoomModel::loadMockEntity(const QString& id) const {
    QString fileName = QString("%1.mock").arg(id);
    QDir mockPath = QDir::current();
    QJsonObject json;

    mockPath.cdUp();
    mockPath.cd ("debug-mock-entities");

    QString filePath = mockPath.filePath(fileName);

    if(QFile::exists(filePath)) {
        QFile mockFile(filePath);

        if(mockFile.open(QFile::ReadOnly|QFile::ExistingOnly|QFile::Text)) {
            const QString jsonText = mockFile.readAll();

            if(!jsonText.isEmpty()) {
                QJsonParseError parseError;
                QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonText.toUtf8(), &parseError);

                if(parseError.error == QJsonParseError::NoError && jsonDoc.isObject()) {
                    json = jsonDoc.object();
                    json.insert ("$_mock_object", true);
                }
            }

            mockFile.close();
        }
    }

    return json;
}
#endif // _DEBUG_LOAD_MOCK_ENTITIES
