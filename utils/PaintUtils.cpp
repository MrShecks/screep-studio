/*
 * File: PaintUtils.cpp
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

#include <QtMath>

#include "PaintUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PaintUtils
// Utility class containing a collection of helper methods for painting with the QPainter device
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPainterPath PaintUtils::roundRectPath(const QRectF& rect, CornerFlags flags) {
    QPainterPath path;

    if(flags == CornerFlag_None)
        path.addRect(rect);
    else if (flags == CornerFlag_All)
        path.addEllipse(rect);
    else {
        path = QPainterPath(QPoint(rect.center().x(), rect.top()));

        path.setFillRule (Qt::WindingFill);

        if(flags & CornerFlag_TopRight) {
            path.arcTo(rect, 90, -90);
        } else {
            path.lineTo(rect.topRight());
            path.lineTo(rect.right(), rect.center().y());
        }

        if(flags & CornerFlag_BottomRight) {
            path.arcTo(rect, 0, -90);
        } else {
            path.lineTo(rect.bottomRight());
            path.lineTo(rect.center().x(), rect.bottom());
        }

        if(flags & CornerFlag_BottomLeft) {
            path.arcTo(rect, -90, -90);
        } else {
            path.lineTo(rect.bottomLeft());
            path.lineTo(rect.left(), rect.center().y());
        }

        if(flags & CornerFlag_TopLeft) {
            path.arcTo(rect, -180, -90);
        } else {
            path.lineTo(rect.topLeft());
            path.lineTo(rect.center().x(), rect.top());
        }

        path.closeSubpath();
    }

    return path;
}

QPainterPath PaintUtils::octagonalPath(const QRectF& rect) {
    const qreal rx = rect.width() / 2;
    const qreal ry = rect.height() / 2;
    const qreal a = qMin(rx, ry) * (2 - qSqrt(2));
    QPainterPath path;

    path.moveTo(rx, ry - a);
    path.lineTo(rx - a, ry);
    path.lineTo(a - rx, ry);
    path.lineTo(-rx, ry - a);
    path.lineTo(-rx, a - ry);
    path.lineTo(a - rx, -ry);
    path.lineTo(rx - a, -ry);
    path.lineTo(rx, a - ry);
    path.lineTo(rx, ry - a);

    return path;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PaintUtils::PaintUtils() {

}
