/*
 * File: RoomGraphicsItemNuker.cpp
 * Created: 2019-1-23
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

#include "RoomGraphicsItemNuker.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemNuker
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemNuker::RoomGraphicsItemNuker(const NukerEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Nuker, entity, cellSize, ItemZOrder_Nuker, parent),
      _nukerRenderer(this) {

    _nukerRenderer.setEnergy(entity.energy());
    _nukerRenderer.setEnergyCapacity(entity.energyCapacity());

    _nukerRenderer.setResources(entity.resources());
    _nukerRenderer.setResourceCapacity(entity.resourceCapacity());
}

RoomGraphicsItemNuker::~RoomGraphicsItemNuker() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemNuker::itemSize(const QSize& cellSize) const {
    return _nukerRenderer.size(cellSize);
}

void RoomGraphicsItemNuker::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _nukerRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemNuker::beginUpdate(const NukerEntity& current, const NukerEntity& updated) {

    if(current.energy() != updated.energy())
        _nukerRenderer.setEnergy(updated.energy());

    if(current.energyCapacity() != updated.energyCapacity())
        _nukerRenderer.setEnergyCapacity(updated.energyCapacity());

    if(current.resources() != updated.resources())
        _nukerRenderer.setResources(updated.resources());

    if(current.resourceCapacity() != updated.resourceCapacity())
        _nukerRenderer.setResourceCapacity(updated.resourceCapacity());

    return _nukerRenderer.isDirty();
}

