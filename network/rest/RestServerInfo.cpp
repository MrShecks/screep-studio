/*
 * File: RestServerInfo.cpp
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

#include "RestServerInfo.h"

//
// Example Response (from private server)
//
//{
//    "ok": 1,
//    "protocol": 13,
//    "useNativeAuth": false,
//    "users": 2,
//    "serverData": {
//        "welcomeText": "<h4>Welcome to your own Screeps private server!</h4>This text can be changed by adding a mod to your server, see <code>mods.json</code> file in your server folder.",
//        "customObjectTypes": {},
//        "historyChunkSize": 20,
//        "socketUpdateThrottle": 1000,
//        "renderer": {
//            "resources": {},
//            "metadata": {}
//        }
//    },
//    "packageVersion": "3.1.7"
//}

// Example Response (from live server)
// Note: The differences in types even though the protocol version are the same, e.g "package" should probably be treated as a string.
//
//{
//  "ok": 1,
//  "package": 145,
//  "protocol": 13,
//  "serverData": {
//    "historyChunkSize": 100,
//    "shards": [
//      "shard0",
//      "shard1",
//      "shard2",
//      "shard3"
//    ]
//  }
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestResponseServerInfo
// REST response class used to parse the response form the /api/version REST endpoint
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ServerData::ServerData() {

}

ServerData::ServerData(const QJsonObject& json)
    : _json(json) {

    if(JSONUtils::hasArray(json, "shards")) {
        _shards = JSONUtils::toStringList(json["shards"].toArray());
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestResponseServerInfo::RestResponseServerInfo(const RestResponse& response)
    : _super(response) {

    if(isSuccess() && body().isObject()) {
        _json = body().object();

        if(JSONUtils::hasObject(_json, "serverData"))
            _serverData = ServerData(_json["serverData"].toObject());
    }
}

RestResponseServerInfo::~RestResponseServerInfo() {

}
