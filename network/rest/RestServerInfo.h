/*
 * File: RestServerInfo.h
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

#ifndef _RESTSERVERINFO_H
#define _RESTSERVERINFO_H

#include "../RestNetworkManager.h"
#include "../../utils/JSONUtils.h"
#include "../../ScreepsApi.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestRequestServerInfo
// Request information about the current server version
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestRequestServerInfo : public RESTRequestBuilder {
    typedef RESTRequestBuilder _super;

public:
    RestRequestServerInfo()
        :_super (Screeps::PATH_SERVER_VERSION) {

    }

    virtual ~RestRequestServerInfo() {

    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestResponseServerInfo
// REST response class used to parse the response form the /api/version REST endpoint
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ServerData {
    friend class RestResponseServerInfo;

public:
    bool hasShards() const                      { return !_shards.isEmpty(); }
    const QStringList& shards() const           { return _shards; }

    int historyChunkSize() const                { return JSONUtils::getInt(_json, "historyChunkSize"); }
    int socketUpdateThrottle() const            { return JSONUtils::getInt(_json, "socketUpdateThrottle"); }

    QString welcomeText() const                 { return JSONUtils::getString(_json, "welcomeText"); }

private:
    QJsonObject _json;
    QStringList _shards;

    ServerData();
    ServerData(const QJsonObject& json);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestResponseServerInfo : public RestResponse {
    typedef RestResponse _super;

public:
    RestResponseServerInfo(const RestResponse& response);
    virtual ~RestResponseServerInfo();

    int protocol() const                        { return JSONUtils::getInt(_json, "protocol"); }
    int users() const                           { return JSONUtils::getInt(_json, "users"); }

    bool useNativeAuth() const                  { return JSONUtils::getBool(_json, "useNativeAuth"); }
    QString packageVersion() const              { return JSONUtils::getString(_json, "packageVersion"); }

    const ServerData& serverData() const        { return _serverData; }

private:
    QJsonObject _json;
    ServerData _serverData;
};

#endif // _RESTSERVERINFO_H
