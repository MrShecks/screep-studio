/*
 * File: SocketEventConsole.cpp
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

#include <QJsonObject>
#include <QJsonArray>

#include "SocketEventConsole.h"
#include "../../utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketEventConsole
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SocketEventConsole::SocketEventConsole(const SocketEventUser& response)
    : _super(response) {

}

SocketEventConsole::~SocketEventConsole() {

}

QStringList SocketEventConsole::logMessages() const {
    const QJsonObject messages = JSONUtils::getObject(json().object(), "messages");

    return JSONUtils::hasArray(messages, "log")
            ? JSONUtils::toStringList(messages["log"].toArray())
            : QStringList();
}

QStringList SocketEventConsole::commandResults() const {
    const QJsonObject messages = JSONUtils::getObject(json().object(), "messages");

    return JSONUtils::hasArray(messages, "results")
            ? JSONUtils::toStringList(messages["results"].toArray())
            : QStringList();
}

QString SocketEventConsole::errorMessage() const {

    return JSONUtils::getString (json().object (), "error");
}
