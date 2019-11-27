/*
 * File: RoomGraphicsItemEnergy.cpp
 * Created: 2019-1-18
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

#include "RoomGraphicsItemEnergy.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemEnergy
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemEnergy::RoomGraphicsItemEnergy(const EnergyEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Energy, entity, cellSize, ItemZOrder_Energy, parent),
      _energyRenderer(this) {

    _energyRenderer.setEnergy(entity.energy());
    _energyRenderer.setEnergyCapacity(entity.energyCapacity());
}

RoomGraphicsItemEnergy::~RoomGraphicsItemEnergy() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemEnergy::itemSize(const QSize& cellSize) const {
    return _energyRenderer.size(cellSize);
}

void RoomGraphicsItemEnergy::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _energyRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemEnergy::beginUpdate(const EnergyEntity& current, const EnergyEntity& updated) {

    if(current.energy() != updated.energy())
        _energyRenderer.setEnergy(updated.energy());

    if(current.energyCapacity() != updated.energyCapacity())
        _energyRenderer.setEnergyCapacity(updated.energyCapacity());

    return _energyRenderer.isDirty();
}
