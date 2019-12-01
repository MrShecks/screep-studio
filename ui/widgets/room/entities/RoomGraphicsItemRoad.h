/*
 * File: RoomGraphicsItemRoad.h
 * Created: 2019-1-4
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

#ifndef _ROOMGRAPHICSITEMROAD_H
#define _ROOMGRAPHICSITEMROAD_H

#include "RoomGraphicsItem.h"
#include "../renderers/RoadRenderer.h"
#include "models/room/RoomUtils.h"
#include "utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoadEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoadEntity : public RoomEntity {
    typedef RoomEntity _super;

public:

    RoadEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    RoomUtils::NeighbourFlags neighbours() const {
        return static_cast<RoomUtils::NeighbourFlags>(JSONUtils::getInt(getMetaData(), "neighbours"));
    }

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemRoad
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemRoad : public TRoomGraphicsItem<RoadEntity> {
    typedef TRoomGraphicsItem<RoadEntity> _super;

public:
    RoomGraphicsItemRoad(const RoadEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemRoad();

private:
    RoadRenderer _roadRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const RoadEntity& current, const RoadEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMROAD_H
