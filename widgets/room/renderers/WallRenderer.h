/*
 * File: WallRenderer.h
 * Created: 2019-1-27
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

#ifndef _WALLRENDERER_H
#define _WALLRENDERER_H

#include <QPainterPath>

#include "EntityRenderer.h"
#include "../../../models/room/RoomUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WallRenderer
// Utility class to draw the "Constructed Wall" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WallRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

public:

    WallRenderer(QObject* parent = nullptr);
    virtual ~WallRenderer();

    void setNeighbours(RoomUtils::NeighbourFlags neighbours);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    //
    // WallRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    mutable QPainterPath _wallPath;

    RoomUtils::NeighbourFlags _neighbours;

    QPainterPath basePath(const QRectF& rect, RoomUtils::NeighbourFlags neighbours) const;
};

#endif // _WALLRENDERER_H
