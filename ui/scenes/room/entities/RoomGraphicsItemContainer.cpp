/*
 * File: RoomGraphicsItemContainer.cpp
 * Created: 2019-1-6
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

#include "RoomGraphicsItemContainer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemContainer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemContainer::RoomGraphicsItemContainer(const ContainerEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Container, entity, cellSize, ItemZOrder_Container, parent),
      _containerRenderer(this) {

    _containerRenderer.setPower(entity.power());
    _containerRenderer.setEnergy(entity.energy());
    _containerRenderer.setTotalResources(entity.getTotalResources());
    _containerRenderer.setResourceCapacity(entity.energyCapacity());
}

RoomGraphicsItemContainer::~RoomGraphicsItemContainer() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemContainer::itemSize(const QSize& cellSize) const {
    return _containerRenderer.size(cellSize);
}

void RoomGraphicsItemContainer::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _containerRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemContainer::beginUpdate(const ContainerEntity& current, const ContainerEntity& updated) {

    if(current.energy() != updated.energy())
        _containerRenderer.setEnergy(updated.energy());

    if(current.power()!= updated.power())
        _containerRenderer.setPower(updated.power());

    const int currentTotalResources = current.getTotalResources();
    const int updatedTotalResources = updated.getTotalResources();

    if(currentTotalResources != updatedTotalResources)
        _containerRenderer.setTotalResources(updatedTotalResources);

    if(current.energyCapacity()!= updated.energyCapacity())
        _containerRenderer.setResourceCapacity(updated.energyCapacity());

    return _containerRenderer.isDirty();
}
