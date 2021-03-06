/*
 * File: SocketCommandSubscribe.h
 * Created: 2018-12-5
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

#ifndef _SOCKETCOMMANDSUBSCRIBE_H
#define _SOCKETCOMMANDSUBSCRIBE_H

#include "../SocketNetworkManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketCommandSubscribe
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SocketCommandSubscribe : public SocketCommandBuilder {
    typedef SocketCommandBuilder _super;

public:
    SocketCommandSubscribe(const QString& channel, const QString& objectName = QString())
        : _super("subscribe") {

        if(objectName.isEmpty())
            addParam(channel);
        else
            addParam(QString("%1:%2").arg(channel).arg(objectName));
    }

    virtual ~SocketCommandSubscribe() {

    }
};

#endif // _SOCKETCOMMANDSUBSCRIBE_H
