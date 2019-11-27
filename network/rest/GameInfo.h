/*
 * File: GameInfo.h
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

#ifndef _GAMEINFO_H
#define _GAMEINFO_H

#include "ScreepsApi.h"
#include "../RestNetworkManager.h"
#include "utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GameTimeRequest (HTTP GET)
// Request the current game time
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameTimeRequest : public RESTRequestBuilder {
    typedef RESTRequestBuilder _super;

public:
    GameTimeRequest();
    virtual ~GameTimeRequest();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GameTimeResponse : public RestResponse {
    typedef RestResponse _super;

public:
    GameTimeResponse(const RestResponse& response);
    virtual ~GameTimeResponse();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestRequestWorldSize (HTTP GET)
// Request the world size for a given shard
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WorldSizeRequest : public RESTRequestBuilder {
    typedef RESTRequestBuilder _super;

public:
    WorldSizeRequest(const QString& shardName = QString());
    virtual ~WorldSizeRequest();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WorldSizeResponse : public RestResponse {
    typedef RestResponse _super;

public:
    WorldSizeResponse(const RestResponse& response);
    virtual ~WorldSizeResponse();

    int width() const                           { return JSONUtils::getInt(body().object(), "width"); }
    int height() const                          { return JSONUtils::getInt(body().object(), "height"); }
};

#endif // _GAMEINFO_H
