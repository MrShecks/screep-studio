/*
 * File: RampartRenderer.h
 * Created: 2019-1-24
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

#ifndef RAMPARTRENDERER_H
#define RAMPARTRENDERER_H

#include <QPainterPath>

#include "EntityRenderer.h"
#include "../../../models/room/RoomUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RampartRenderer
// Utility class to draw the "Rampart" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RampartRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static constexpr qreal ENTITY_OPACITY       = 0.2f;

    static const int BORDER_PEN_SCALE           = 4;

public:

    RampartRenderer(QObject* parent = nullptr);
    virtual ~RampartRenderer();

    void setNeighbours(RoomUtils::NeighbourFlags neighbours);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    void setOpacity(qreal opacity);

    //
    // RampartRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    mutable QPainterPath _rampartPath;
    mutable QPainterPath _edgePath;
    qreal _opacity;

    RoomUtils::NeighbourFlags _neighbours;

    QPainterPath basePath(const QRectF& rect, RoomUtils::NeighbourFlags neighbours) const;
    QPainterPath edgePath(const QRectF& rect, RoomUtils::NeighbourFlags neighbours, qreal penWidth) const;
};

#endif // RAMPARTRENDERER_H
