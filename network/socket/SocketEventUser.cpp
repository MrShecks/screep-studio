/*
 * File: SocketEventUser.cpp
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

#include <QStringList>

#include "SocketEventUser.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketEventUser
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SocketEventUser::SocketEventUser(const SocketResponse& response)
    : _super(response) {

    const QStringList s = response.stream ().split ("/");
    Q_ASSERT_X(s.length () == 2, "SocketEventUser::SocketEventUser", "Expected user stream formated as \"userId/objectId\"");

    _userId = s[0];
    _objectId = s[1];
}

SocketEventUser::~SocketEventUser() {

}

bool SocketEventUser::objectIdMatches(const QString& objectId) const {
    return _objectId.compare(objectId, Qt::CaseInsensitive) == 0;
}
