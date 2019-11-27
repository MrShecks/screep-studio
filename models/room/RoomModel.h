/*
 * File: RoomModel.h
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

#ifndef _ROOMMODEL_H
#define _ROOMMODEL_H

#include <QObject>
#include <QPointer>
#include <QString>
#include <QMap>

#include "RoomTerrainModel.h"
#include "RoomEntityModel.h"
#include "RoomEntity.h"

#include "StateMachineOpen.h"

#include "../NetworkModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _DEBUG_ROOM_MODEL               1
#define _DEBUG_LOAD_MOCK_ENTITIES       _DEBUG_ROOM_MODEL && 1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomModel()
// Complete representation of a single world room
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomModel : public QObject {
    typedef QObject _super;

    Q_OBJECT

    friend class StateMachineOpen;

public:
    typedef QSharedPointer<RoomModel> TSharedPtr;

    static const int ROOM_WIDTH = RoomTerrainModel::ROOM_WIDTH;
    static const int ROOM_HEIGHT = RoomTerrainModel::ROOM_HEIGHT;

    explicit RoomModel(NetworkModel* networkModel, const QString& roomName, const QString& shardName, QObject* parent = nullptr);
    virtual ~RoomModel();

    void open();
    void close();

    bool isOpen() const                             { return _isOpen; }

    const QString& id() const                       { return _id; }
    const QString& roomName() const                 { return _roomName; }
    const QString& shardName() const                { return _shardName; }

    const RoomTerrainModel& terrainModel() const    { return _terrainModel; }

signals:
    void roomEntityAdded(const QString& id, const RoomEntity& entity);
    void roomEntityUpdated(const QString& id, const RoomEntity& entity, int gameTime);
    void roomEntityRemoved(const QString& id);

    void roomTerrainReceived();
    void roomEntitiesReceived();

private slots:
    void _refreshTerrain();
    void _refreshEntities();

    void _onRoomTerrainReceived(const RestResponseRoomTerrain& response);
    void _onRoomEventReceived(const SocketEventRoom& event);

private:
    QPointer<NetworkModel> _networkModel;

    QString _id;
    QString _roomName;
    QString _shardName;

    StateMachineOpen* _stateMachineOpen;

    RoomTerrainModel _terrainModel;
    RoomEntityModel _entityModel;

    QStateMachine _openStateMachine;
    bool _isOpen;

#if _DEBUG_LOAD_MOCK_ENTITIES
    QJsonObject loadMockEntity(const QString& id) const;
#endif // _DEBUG_LOAD_MOCK_ENTITIES
};

#endif // _ROOMMODEL_H
