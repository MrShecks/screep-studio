/*
 * File: RoomGraphicsItemTombstone.cpp
 * Created: 2018-12-29
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

#include <QPainter>

#include "RoomGraphicsItemTombstone.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemTombstone
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemTombstone::RoomGraphicsItemTombstone(const TombstoneEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Tombstone, entity, cellSize, ItemZOrder_Tombstone, parent),
      _tombstoneRenderer(this) {

    _tombstoneRenderer.setTotalResources(entity.getTotalResources());
}

RoomGraphicsItemTombstone::~RoomGraphicsItemTombstone() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemTombstone::itemSize(const QSize& cellSize) const {
    return _tombstoneRenderer.size(cellSize);
}

void RoomGraphicsItemTombstone::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _tombstoneRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemTombstone::beginUpdate(const TombstoneEntity& current, const TombstoneEntity& updated) {

    return _tombstoneRenderer.isDirty();
}
