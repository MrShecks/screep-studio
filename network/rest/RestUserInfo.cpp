/*
 * File: RestUserInfo.cpp
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

#include "RestUserInfo.h"
#include "../../utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestResponseUserInfo()
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Example response
//
//{
//    "_id":"f99b7db35b10edd",
//    "badge":{
//        "color1":"#00770e",
//        "color2":"#ffffff",
//        "color3":"#ffff00",
//        "flip":false,
//        "param":0,
//        "type":3
//    },
//    "blocked":false,
//    "cpu":100,
//    "gcl":0,
//    "money":0,
//    "ok":1,
//    "password":true,
//    "steam":{
//        "id":"55512345678900000"
//    },
//    "username":"Fred"
//}

RestResponseUserInfo::RestResponseUserInfo(const RestResponse& response)
    : _super(response) {

    if(isSuccess ()) {
        const QJsonObject json = body().object();

        _id = JSONUtils::getString(json, "_id");
        _userName = JSONUtils::getString(json, "username");

        _cpu = JSONUtils::getInt(json, "cpu");
        _gcl = JSONUtils::getInt(json, "gcl");
        _money = JSONUtils::getInt(json, "money");

        _isBlocked = JSONUtils::getBool(json, "blocked");

        if(JSONUtils::hasObject(json, "badge")) {
            _badge = Badge(json["badge"].toObject());
        }
    }
}

RestResponseUserInfo::~RestResponseUserInfo() {

}
