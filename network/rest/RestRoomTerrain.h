/*
 * File: RestRoomTerrain.h
 * Created: 2018-11-28
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

#ifndef _RESTROOMTERRAIN_H
#define _RESTROOMTERRAIN_H

#include "ScreepsApi.h"
#include "../RestNetworkManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestRequestRoomTerrain (HTTP GET)
// REST request to retrieve information about the terrain for a given room
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestRequestRoomTerrain : public RESTRequestBuilder {
    typedef RESTRequestBuilder _super;

public:
    RestRequestRoomTerrain(const QString& roomName, const QString& shardName = QString())
        : _super(Screeps::PATH_GAME_ROOMTERRAIN) {

        addQueryItem(Screeps::QUERY_ROOM_NAME, roomName);
        addQueryItem(Screeps::QUERY_ENCODED, 1);

        if(!shardName.isEmpty())
            addQueryItem(Screeps::QUERY_SHARD_NAME, shardName);
    }

    virtual ~RestRequestRoomTerrain() {

    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestResponseRoomTerrain
// REST response class use to parse the response form the /api/room-terrain REST endpoint
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestResponseRoomTerrain : public RestResponse {
    typedef RestResponse _super;

public:
    class Room;
    typedef QList<Room> TRoomList;

    RestResponseRoomTerrain(const RestResponse& response);
    virtual ~RestResponseRoomTerrain();

    const QString& roomName() const             { return _roomName; }
    const QString& shardName() const            { return _shardName; }

    const Room& room() const;
    const TRoomList& rooms() const;

private:
    QString _roomName;
    QString _shardName;

    TRoomList _rooms;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestResponseRoomTerrain::Room {
    friend class RestResponseRoomTerrain;

public:
    QString id() const          { return _id; }
    QString type() const        { return _type; }
    QString name() const        { return _name; }
    QString terrain() const     { return _terrain; }

    int width() const           { return Screeps::ROOM_WIDTH; }
    int height() const          { return Screeps::ROOM_HEIGHT; }

    Screeps::TerrainFlags getCell(int x,  int y, Screeps::TerrainFlags defaultType = Screeps::TerrainFlag_None) const;

private:
    QString _id;
    QString _type;
    QString _name;
    QString _terrain;

    Room(const QJsonObject& json);
};

#endif // _RESTROOMTERRAIN_H
