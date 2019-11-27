/*
 * File: RoomGraphicsItemRampart.cpp
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

#include <QPainter>

#include "RoomGraphicsItemRampart.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemRampart
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemRampart::RoomGraphicsItemRampart(const RampartEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Rampart, entity, cellSize, ItemZOrder_Rampart, parent),
      _rampartRenderer(this) {

    _rampartRenderer.setNeighbours(entity.neighbours());
}

RoomGraphicsItemRampart::~RoomGraphicsItemRampart() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemRampart::itemSize(const QSize& cellSize) const {
    return _rampartRenderer.size(cellSize);
}

void RoomGraphicsItemRampart::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _rampartRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemRampart::beginUpdate(const RampartEntity& current, const RampartEntity& updated) {

    if(current.neighbours() != updated.neighbours())
        _rampartRenderer.setNeighbours(updated.neighbours());

    return _rampartRenderer.isDirty();
}

