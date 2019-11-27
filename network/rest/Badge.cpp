/*
 * File: Badge.cpp
 * Created: 2018-12-3
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

#include "Badge.h"
#include "../../utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Badge()
// Utility class used to parse the "badge" JSON object which represents a user or room badge
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Exmaple:
//
//    "badge":{
//        "color1":"#00770e",
//        "color2":"#ffffff",
//        "color3":"#ffff00",
//        "flip":false,
//        "param":0,
//        "type":3
//    },

Badge::Badge()
    : _type(0), _param(0), _isFlipped(false) {

}

Badge::Badge(const QJsonObject& json) {

    _type = JSONUtils::getInt(json, "type");

    _color1.setNamedColor(JSONUtils::getString(json, "color1"));
    _color2.setNamedColor(JSONUtils::getString(json, "color2"));
    _color3.setNamedColor(JSONUtils::getString(json, "color3"));

    _isFlipped = JSONUtils::getBool(json, "flip");
    _param = JSONUtils::getInt(json, "param");
}
