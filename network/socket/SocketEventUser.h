/*
 * File: SocketEventUser.h
 * Created: 2018-12-9
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

#ifndef SOCKETEVENTUSER_H
#define SOCKETEVENTUSER_H

#include "network/SocketNetworkManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketEventUser
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SocketEventUser : public SocketResponse {
    typedef SocketResponse _super;

public:
    SocketEventUser(const SocketResponse& response);
    virtual ~SocketEventUser();

    const QString& userId() const               { return _userId; };
    const QString& objectId() const             { return _objectId; }

    bool objectIdMatches(const QString& objectId) const;

private:
    QString _userId;
    QString _objectId;
};


#endif // SOCKETEVENTUSER_H
