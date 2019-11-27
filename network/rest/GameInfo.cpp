/*
 * File: GameInfo.cpp
 * Created: 2019-1-30
 *
 * Copyright (c) shecks 2019 <shecks@gmail.com>
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

#include "GameInfo.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GameTimeRequest (HTTP GET)
// Request the current game time
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameTimeRequest::GameTimeRequest()
    : _super(Screeps::PATH_GAME_TIME) {

}

GameTimeRequest::~GameTimeRequest() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameTimeResponse::GameTimeResponse(const RestResponse& response)
    : _super(response) {

}

GameTimeResponse::~GameTimeResponse() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WorldSizeRequest (HTTP GET)
// Request the world size for a given shard
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WorldSizeRequest::WorldSizeRequest(const QString& shardName /* = QString() */)
    :_super (Screeps::PATH_GAME_WORLDSIZE) {

    if(!shardName.isEmpty())
        addQueryItem(Screeps::QUERY_SHARD_NAME, shardName);
}

WorldSizeRequest::~WorldSizeRequest() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WorldSizeResponse::WorldSizeResponse(const RestResponse& response)
    : _super(response) {

}

WorldSizeResponse::~WorldSizeResponse() {

}
