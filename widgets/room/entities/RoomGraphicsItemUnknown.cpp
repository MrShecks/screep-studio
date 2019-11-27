/*
 * File: RoomGraphicsItemUnknown.cpp
 * Created: 2018-12-11
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

#include "RoomGraphicsItemUnknown.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemUnknown
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemUnknown::RoomGraphicsItemUnknown(const RoomEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Unknown, entity, cellSize, ItemZOrder_Default, parent),
      _unknownRenderer(this) {

}

RoomGraphicsItemUnknown::~RoomGraphicsItemUnknown() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemUnknown::itemSize(const QSize& cellSize) const {
    return _unknownRenderer.size(cellSize);
}

void RoomGraphicsItemUnknown::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _unknownRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

