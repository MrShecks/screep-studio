/*
 * File: RestAuthentication.h
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

#ifndef _RESTAUTHENTICATION_H
#define _RESTAUTHENTICATION_H

#include "ScreepsApi.h"
#include "../RestNetworkManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestRequestUserSignin (HTTP POST)
// Authenticate the user using username and password. Note: This method has been deprecated on the live server
// and is only available on private servers with the "screepsmod-auth" mod installed and the user password has
// been added to the game servers database.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestRequestUserSignin : public RESTRequestBuilder {
    typedef RESTRequestBuilder _super;

public:
    RestRequestUserSignin(const QString& email, const QString& password)
        : _super(Screeps::PATH_AUTH_SIGNIN) {

        addBodyItem(Screeps::POST_EMAIL, email);
        addBodyItem(Screeps::POST_PASSWORD, password);
    }

    virtual ~RestRequestUserSignin() {

    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestRequestTicketSignin
// Authenticate the client using the users Steam ticket
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestRequestTicketSignin : public RESTRequestBuilder {
    typedef RESTRequestBuilder _super;

public:
    RestRequestTicketSignin(const QString& ticket, bool nativeAuth = false)
        : _super(Screeps::PATH_AUTH_STEAM_TOKEN)     {

        addBodyItem(Screeps::POST_AUTH_TICKET, ticket);
        addBodyItem(Screeps::POST_AUTH_NATIVE, nativeAuth);
    }

    virtual ~RestRequestTicketSignin() {

    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestRequestUserSignin
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestResponseUserSignin : public RestResponse {
    typedef RestResponse _super;

public:
    RestResponseUserSignin(const RestResponse& response);
    virtual ~RestResponseUserSignin();

    const QString& token() const                { return _token; }

private:
    QString _token;
};

#endif // _RESTAUTHENTICATION_H
