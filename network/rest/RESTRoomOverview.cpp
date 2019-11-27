/*
 * File: RoomOverview.cpp
 * Created: 2018-11-29
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

#include "RESTRoomOverview.h"
#include "../../utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomOverviewResponse()
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Example Response
//
//{
//    "ok":1,
//    "owner":{
//        "badge":{
//            "color1":"#166b9c",
//            "color2":"#e1da64",
//            "color3":"#b5fb01",
//            "flip":false,
//            "param":26,
//            "type":12
//        },
//        "username":"JackBot"
//    },
//    "stats":{
//    },
//    "statsMax":{
//    },
//    "totals":{
//    }
//}

RESTResponseRoomOverview::RESTResponseRoomOverview(const RestResponse& response)
    : _super(response) {

    if(isSuccess()) {
        const QJsonObject json = body().object();

        if(JSONUtils::hasObject(json, "owner")) {
            const QJsonObject owner = json["owner"].toObject();

            _ownerName = JSONUtils::getString(owner, "username");

            if(JSONUtils::hasObject(owner, "badge"))
                _ownerBadge = Badge(owner["badge"].toObject ());

            // TODO: stats, statsMax and totals ...
        }
    }
}

RESTResponseRoomOverview::~RESTResponseRoomOverview() {

}
