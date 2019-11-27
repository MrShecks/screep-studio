/*
 * File: SocketEventRoom.h
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

#ifndef SOCKETEVENTROOM_H
#define SOCKETEVENTROOM_H

#include <QList>
#include <QStringList>
#include <QJsonObject>

#include "../SocketNetworkManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketEventRoom
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SocketEventRoom : public SocketResponse {
    typedef SocketResponse _super;

public:
    class RoomEntity;

    typedef QList<RoomEntity> TRoomEntityList;

    SocketEventRoom(const SocketResponse& response);
    virtual ~SocketEventRoom();

    int gameTime() const                        { return _gameTime; }

    const QString& roomName() const             { return _roomName; }
    const QString& shardName() const            { return _shardName; }

    const TRoomEntityList& entities() const     { return _entities; }

    bool hasShard() const                       { return !_shardName.isEmpty(); }

private:
    int _gameTime;

    QString _roomName;
    QString _shardName;

    TRoomEntityList _entities;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketEventRoom::RoomEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SocketEventRoom::RoomEntity {
    friend class SocketEventRoom;

public:
    virtual ~RoomEntity() {

    }

    const QString& id() const;
    const QJsonObject& json() const;

    bool isRemoved() const;

    QString type() const;

private:
    QString _id;
    QJsonObject _json;

    RoomEntity(const QString& id, const QJsonObject& json = QJsonObject());
};

#endif // SOCKETEVENTROOM_H
