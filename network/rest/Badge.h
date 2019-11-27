/*
 * File: Badge.h
 * Created: 2018-12-3
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

#ifndef _BADGE_H
#define _BADGE_H

#include <QColor>
#include <QJsonObject>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Badge()
// Utility class used to parse the "badge" JSON object which represents a user or room badge
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Badge {

public:
    Badge();
    Badge(const QJsonObject& json);

    int type() const                { return _type; }
    int param() const               { return _param; }

    const QColor& color1() const    { return _color1; }
    const QColor& color2() const    { return _color2; }
    const QColor& color3() const    { return _color3; }

    bool isFlipped() const          { return _isFlipped; }

private:
    int _type;
    int _param;

    QColor _color1;
    QColor _color2;
    QColor _color3;

    bool _isFlipped;
};

#endif // _BADGE_H
