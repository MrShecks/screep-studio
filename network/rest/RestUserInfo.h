/*
 * File: RestUserInfo.h
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

#ifndef _RESTUSERINFO_H
#define _RESTUSERINFO_H

#include "ScreepsApi.h"
#include "network/RestNetworkManager.h"
#include "Badge.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestRequestUserInfo (HTTP GET)
// Request information about the currently authenticated user
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestRequestUserInfo : public RESTRequestBuilder {
    typedef RESTRequestBuilder _super;

public:
    RestRequestUserInfo()
        : _super(Screeps::PATH_AUTH_ME) {

    }

    virtual ~RestRequestUserInfo() {

    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestResponseUserInfo : public RestResponse {
    typedef RestResponse _super;

public:
    RestResponseUserInfo(const RestResponse& response);
    virtual ~RestResponseUserInfo();

    const QString& id() const           { return _id; }
    const QString& userName() const     { return _userName; }

    int cpu() const                     { return _cpu; }
    int gcl() const                     { return _gcl; }
    int money() const                   { return _money; }

    bool isBlocked() const              { return _isBlocked; }

    const Badge& badge() const          { return _badge; }

private:
    QString _id;
    QString _userName;

    int _cpu;
    int _gcl;
    int _money;

    bool _isBlocked;

    Badge _badge;
};

#endif // _RESTUSERINFO_H
