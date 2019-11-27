/*
 * File: RoomGraphicsItemPowerSpawn.cpp
 * Created: 2019-1-31
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

#include "RoomGraphicsItemPowerSpawn.h"
#include "../../../utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PowerSpawnEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemPowerSpawn
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemPowerSpawn::RoomGraphicsItemPowerSpawn(const PowerSpawnEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_PowerSpawn, entity, cellSize, ItemZOrder_PowerSpawn, parent),
      _powerSpawnRenderer(this) {

    _powerSpawnRenderer.setEnergy(entity.energy());
    _powerSpawnRenderer.setEnergyCapacity(entity.energyCapacity());

    _powerSpawnRenderer.setPower(entity.power());
    _powerSpawnRenderer.setPowerCapacity(entity.powerCapacity());
}

RoomGraphicsItemPowerSpawn::~RoomGraphicsItemPowerSpawn() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemPowerSpawn::itemSize(const QSize& cellSize) const {
    return _powerSpawnRenderer.size(cellSize);
}

void RoomGraphicsItemPowerSpawn::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _powerSpawnRenderer.draw (painter, bounds);

    Q_UNUSED(option);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RoomGraphicsItemPowerSpawn::beginUpdate(const PowerSpawnEntity& current, const PowerSpawnEntity& updated) {
    if(current.energy() != updated.energy())
        _powerSpawnRenderer.setEnergy(updated.energy());

    if(current.energyCapacity() != updated.energyCapacity())
        _powerSpawnRenderer.setEnergyCapacity(updated.energyCapacity());

    if(current.power() != updated.power())
        _powerSpawnRenderer.setPower(current.power());

    if(current.powerCapacity() != updated.powerCapacity())
        _powerSpawnRenderer.setPowerCapacity(updated.powerCapacity());

    return _powerSpawnRenderer.isDirty();
}

