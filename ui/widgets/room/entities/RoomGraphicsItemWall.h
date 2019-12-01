/*
 * File: RoomGraphicsItemWall.h
 * Created: 2018-12-15
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

#ifndef _ROOMGRAPHICSITEMWALL_H
#define _ROOMGRAPHICSITEMWALL_H

#include "RoomGraphicsItem.h"
#include "ui/widgets/room/renderers/WallRenderer.h"
#include "utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WallEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WallEntity : public RoomEntity {
    typedef RoomEntity _super;

public:
    WallEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    int hits() const                            { return getInt("hits"); }
    int hitsMax() const                         { return getInt("hitsMax"); }

    RoomUtils::NeighbourFlags neighbours() const {
        return static_cast<RoomUtils::NeighbourFlags>(JSONUtils::getInt(getMetaData(), "neighbours"));
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemWall
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemWall : public TRoomGraphicsItem<WallEntity> {
    typedef TRoomGraphicsItem<WallEntity> _super;

    static const int PEN_WIDTH  = 1;

public:
    RoomGraphicsItemWall(const WallEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemWall();

private:
    WallRenderer _wallRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const WallEntity& current, const WallEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMWALL_H
