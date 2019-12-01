/*
 * File: RoomGraphicsItemRoad.cpp
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

#include "RoomGraphicsItemRoad.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemRoad
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemRoad::RoomGraphicsItemRoad(const RoadEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Road, entity, cellSize, ItemZOrder_Road, parent),
      _roadRenderer(this) {

    _roadRenderer.setNeighbours(entity.neighbours());
}

RoomGraphicsItemRoad::~RoomGraphicsItemRoad() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemRoad::itemSize(const QSize& cellSize) const {
    return _roadRenderer.size(cellSize);
}

void RoomGraphicsItemRoad::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _roadRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemRoad::beginUpdate(const RoadEntity& current, const RoadEntity& updated) {

    if(current.neighbours() != updated.neighbours())
        _roadRenderer.setNeighbours(updated.neighbours());

    return _roadRenderer.isDirty();
}
