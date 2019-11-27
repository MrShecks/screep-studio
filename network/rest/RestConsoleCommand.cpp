/*
 * File: RestConsoleCommand.cpp
 * Created: 2018-12-26
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

#include "RestConsoleCommand.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RestPostConsoleCommand (HTTP POST)
// Send a command to the user console
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RestPostConsoleCommand::RestPostConsoleCommand(const QString& expression, const QString& shard)
    : _super(Screeps::PATH_USER_CONSOLE) {

    addBodyItem(Screeps::POST_EXPRESSION, expression);
    addBodyItem(Screeps::POST_SHARD_NAME, shard);
}

RestPostConsoleCommand::~RestPostConsoleCommand() {

}
