/*
 * File: PaintUtils.h
 * Created: 2019-1-25
 *
 * Copyright (c) shecks 2019 <shecks@gmail.com>
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

#ifndef _PAINTUTILS_H
#define _PAINTUTILS_H

#include <QPainter>
#include <QPainterPath>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PaintUtils
// Utility class containing a collection of helper methods for painting with the QPainter device
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PaintUtils {

public:
    enum Corner {
        TopLeft                                 = 0,
        TopRight                                = 1,
        BottomLeft                              = 2,
        BottomRight                             = 3
    };

    enum CornerFlag {
        CornerFlag_None                         = 0,

        CornerFlag_TopLeft                      = 1 << TopLeft,
        CornerFlag_TopRight                     = 1 << TopRight,
        CornerFlag_BottomLeft                   = 1 << BottomLeft,
        CornerFlag_BottomRight                  = 1 << BottomRight,

        CornerFlag_All                          = CornerFlag_TopLeft | CornerFlag_TopRight | CornerFlag_BottomLeft | CornerFlag_BottomRight
    };

    Q_DECLARE_FLAGS(CornerFlags, CornerFlag)

    static QPainterPath roundRectPath(const QRectF& rect, CornerFlags flags);
    static QPainterPath octagonalPath(const QRectF& rect);

private:
    PaintUtils();
};

Q_DECLARE_OPERATORS_FOR_FLAGS(PaintUtils::CornerFlags);

#endif // _PAINTUTILS_H
