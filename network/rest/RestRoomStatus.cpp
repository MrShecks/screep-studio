/*
 * File: RESTRoomStatus.cpp
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

#include <QJsonObject>

#include "RestRoomStatus.h"
#include "utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomStatusResponse()
// REST response class use to parse the response form the /api/game/room-status REST endpoint
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Example Response
//
//{
//    "ok":1,
//    "room": {
//        "status": "normal"
//    }
//}

// Note: From the game.js source it looks like the returned "room" object can
// contain "status", "novice" and "openTime" keys. Need to find out what these
// are and how to generate the test data.

RestResponseRoomStatus::RestResponseRoomStatus(const RestResponse& response)
    : _super(response) {

    if(isSuccess ()) {
        const QJsonObject json = body().object();
        Q_ASSERT(JSONUtils::hasObject(json, "room"));

        if(JSONUtils::hasObject(json, "room")) {
            const QJsonObject room = json["room"].toObject();

            _status = JSONUtils::getString(room, "status");
        }
    }
}

RestResponseRoomStatus::~RestResponseRoomStatus() {

}

