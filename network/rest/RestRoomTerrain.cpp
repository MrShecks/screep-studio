/*
 * File: RestRoomTerrain.cpp
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

#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>

#include "RestRoomTerrain.h"
#include "utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestResponseRoomTerrain
// REST response class use to parse the response form the /api/room-terrain REST endpoint
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Example Response
//
//{
//    "ok": 1,
//    "terrain": [
//        {
//            "room": "W8N3",
//            "terrain": "11111111111111111111111111111111111111111111111111
//                        11111111111111111111111111111111111111111111111111
//                        11111111111111111111111111111111111111111111111111
//                        11111111111111111111111111111111111111111111111111
//                        11111111111111111111111111111111111111111111111111
//                        11111111111100000000000000000000000000000000000000
//                        11111111110000000000000000000000000000000000000000
//                        11111111000000000000000000000000000000000000000000
//                        11111110000000000000000000000000000000000000000000
//                        11111110000000000000000000000000000000000000000000
//                        11111100000000000000000000000000000000000000000000
//                        11111100000000000000000000000000000000000000000000
//                        11111000000000000000000000000000000000000000000000
//                        11111000000000000000000000000000000000000000000000
//                        11110000000000000000000000000000000000000000000000
//                        11110000000000000000000000000000000000000000000000
//                        11100000000000000000000000000000000000000000000000
//                        11100000000000000000000000000000000000000011000000
//                        11000000000000000000000000000000000000000111100000
//                        11000000000000000000000000000000000000001111100000
//                        11000000000000000000000000000000001100011111000000
//                        11000000000000000000000000000110001110011110000000
//                        11000000000000000000000000001111000110011100000000
//                        11000011000000000000000000001111000000011000000000
//                        11000011000000000000000000000000000000000000000000
//                        11000000000000000000000000000000000000000000000000
//                        11000000000000000000010000000000000000000000000000
//                        11000000000000000000111000000000000000000000000000
//                        11000000000000000000111100000000000000000000000000
//                        11000000000000000000111100000000000000000000000000
//                        11000000000000000000011000000000000000000000000000
//                        11100000000000000000000000000000000000000000000000
//                        11100000000000000000000000000000000000000000000000
//                        11110000000000000000000000000000110000000000000000
//                        11110000000000000000000000000001111000000000000000
//                        11111000000000000000000000000001111000000000000000
//                        11111000000000000000000000000000111000000000000000
//                        11111100000000000000000000000000010000000000000000
//                        11111100000000000000000000000000000000000000000000
//                        11111110000000000000000000000000000000000000000000
//                        11111111000000000000000000000000000000000000000000
//                        11111111100000000000000000000000000000111111000000
//                        11111111110000000000000100000000000001111111110000
//                        11111111110000000000001110000000000011111111111000
//                        11111111110000000000000110000000000011111111111100
//                        11111111100000000000000000000000000011111111111100
//                        11111111000000000000000000000000000011111111111100
//                        11111110000000000000000000000000000011111111111111
//                        11111100000000000000000000000000000011111111111111
//                        11111100000000000000000000000000000011111111111111",
//            "type": "terrain",
//            "_id": "d5320772346b54b",
//            "meta": {
//                "revision": 0,
//                "created": 1477476557638,
//                "version": 0
//            },
//            "$loki": 38
//        }
//    ]
//}

RestResponseRoomTerrain::RestResponseRoomTerrain(const RestResponse& response)
    : _super(response) {

    _roomName = queryItemValue(Screeps::QUERY_ROOM_NAME);
    _shardName = queryItemValue(Screeps::QUERY_SHARD_NAME);

    if(!body().isNull () && body().isObject ()) {
        const QJsonObject json = body().object ();
        Q_ASSERT(json.contains("terrain") && json["terrain"].isArray ());

        if(JSONUtils::hasArray(json, "terrain")) {
            QJsonArray terrainArray = json["terrain"].toArray();
            QJsonArray::const_iterator it = terrainArray.constBegin();
            QJsonArray::const_iterator limit = terrainArray.constEnd();

            for(; it != limit; ++it) {
                _rooms.append(Room(it->toObject ()));
            }
        }
    }
}

RestResponseRoomTerrain::~RestResponseRoomTerrain() {

}

const RestResponseRoomTerrain::Room& RestResponseRoomTerrain::room() const {
    Q_ASSERT_X(!_rooms.isEmpty (), "RestResponseRoomTerrain::room", "Expected at least 1 entry in room list.");

    //
    // Note: This is a convienence method used to return the first element
    // of the _rooms list. Although the REST response returns an JSON array of
    // room objects, we only every make a request for a single room so the list
    // should only ever contain a single element.
    //

    return _rooms[0];
}

const RestResponseRoomTerrain::TRoomList& RestResponseRoomTerrain::rooms() const {
    return _rooms;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Screeps::TerrainFlags RestResponseRoomTerrain::Room::getCell(int x,  int y, Screeps::TerrainFlags defaultType /* = Screeps::TerrainFlag_None */) const {
    Screeps::TerrainFlags flags = defaultType;

    if(x >= 0 && x < Screeps::ROOM_WIDTH && y >= 0 && y < Screeps::ROOM_HEIGHT) {
        int type;

        if((type = _terrain.at((y * Screeps::ROOM_WIDTH) + x).digitValue()) != -1) {
            if(type != 0) {
                if(type & Screeps::TERRAIN_MASK_WALL)
                    flags |= Screeps::TerrainFlag_Wall;

                if(type & Screeps::TERRAIN_MASK_SWAMP)
                    flags |= Screeps::TerrainFlag_Swamp;

                if(type & Screeps::TERRAIN_MASK_LAVA)
                    flags |= Screeps::TerrainFlag_Lava;

            } else {
                flags = Screeps::TerrainFlag_Plain;
            }
        }

        Q_ASSERT_X(type != -1, "RestResponseRoomTerrain::Room::getCell", "Non digit terrain type found in REST response");
    }

    return flags;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestResponseRoomTerrain::Room::Room(const QJsonObject& json) {
    Q_ASSERT(json.contains("_id") && json.contains("room") && json.contains("terrain"));

    _id = JSONUtils::getString(json, "_id");
    _type = JSONUtils::getString(json, "type");
    _name = JSONUtils::getString(json, "room");
    _terrain = JSONUtils::getString(json, "terrain");
}
