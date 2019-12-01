/*
 * File: RoomGraphicsItemWall.cpp
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

#include <QPainter>

#include "RoomGraphicsItemWall.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemWall
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemWall::RoomGraphicsItemWall(const WallEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Wall, entity, cellSize, ItemZOrder_Wall, parent),
      _wallRenderer(this) {

    _wallRenderer.setNeighbours(entity.neighbours());
}

RoomGraphicsItemWall::~RoomGraphicsItemWall() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemWall::itemSize(const QSize& cellSize) const {
    return _wallRenderer.size(cellSize);
}

void RoomGraphicsItemWall::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _wallRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemWall::beginUpdate(const WallEntity& current, const WallEntity& updated) {

    if(current.neighbours() != updated.neighbours())
        _wallRenderer.setNeighbours(updated.neighbours());

    return _wallRenderer.isDirty();
}


