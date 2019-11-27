/*
 * File: RESTRoomOverview.h
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

#ifndef _RESTROOMOVERVIEW_H
#define _RESTROOMOVERVIEW_H

#include "ScreepsApi.h"
#include "../RestNetworkManager.h"
#include "Badge.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomOverviewRequest : public RESTRequestBuilder {
    typedef RESTRequestBuilder _super;

public:
    RoomOverviewRequest(const QString& roomName, int interval = 8, const QString& shardName = QString())
        : _super(Screeps::PATH_GAME_ROOMOVERVIEW) {

        addQueryItem("room", roomName);
        addQueryItem("shard", shardName);
        addQueryItem("interval", interval);
    }

    virtual ~RoomOverviewRequest() {

    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RESTResponseRoomOverview : public RestResponse {
    typedef RestResponse _super;

public:
    RESTResponseRoomOverview(const RestResponse& response);
    virtual ~RESTResponseRoomOverview();

    const QString& ownerName() const            { return _ownerName; }
    const Badge& ownerBadge() const             { return _ownerBadge; }

private:
    QString _ownerName;
    Badge _ownerBadge;
};

#endif // _RESTROOMOVERVIEW_H
