/*
 * File: RESTRoomStatus.h
 * Created: 2018-11-30
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

#ifndef _RESTROOMSTATUS_H
#define _RESTROOMSTATUS_H

#include "ScreepsApi.h"
#include "../RestNetworkManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomStatusRequest() (HTTP GET)
// Request the status of a given room and whether it is in the novice area of the map
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomStatusRequest : public RESTRequestBuilder {
    typedef RESTRequestBuilder _super;

public:
    RoomStatusRequest(const QString& roomName, const QString& shardName = QString())
        : _super(Screeps::PATH_GAME_ROOMSTATUS) {

        addQueryItem(Screeps::QUERY_ROOM_NAME, roomName);
        addQueryItem(Screeps::QUERY_SHARD_NAME, shardName);
    }

    virtual ~RoomStatusRequest() {

    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomStatusResponse()
// REST response class use to parse the response form the /api/game/room-status REST endpoint
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestResponseRoomStatus : public RestResponse {
    typedef RestResponse _super;

public:
    RestResponseRoomStatus(const RestResponse& response);
    virtual ~RestResponseRoomStatus();

    const QString& status() const               { return _status; }

private:
    QString _status;
};

#endif // _RESTROOMSTATUS_H
