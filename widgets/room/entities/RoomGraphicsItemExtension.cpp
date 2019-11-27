/*
 * File: RoomGraphicsItemExtension.cpp
 * Created: 2018-12-12
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

#include "RoomGraphicsItemExtension.h"
#include "../../../utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemExtension
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemExtension::RoomGraphicsItemExtension(const ExtensionEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Extension, entity, cellSize, ItemZOrder_Extension, parent),
      _extensionRenderer(this),
      _glow(this) {

    _glow.setScale(GLOW_EFFECT_SCALE);
    _glow.setOpacity(GLOW_EFFECT_OPACITY);
    _glow.setVisible(entity.energy() > 0);

    _extensionRenderer.setEnergy(entity.energy());
    _extensionRenderer.setEnergyCapacity(entity.energyCapacity());
}

RoomGraphicsItemExtension::~RoomGraphicsItemExtension() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemExtension::itemSize(const QSize& cellSize) const {
    return _extensionRenderer.size(cellSize);
}

void RoomGraphicsItemExtension::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _extensionRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemExtension::beginUpdate(const ExtensionEntity& current, const ExtensionEntity& updated) {

    if(current.energy() != updated.energy()) {
        _extensionRenderer.setEnergy(updated.energy());
        _glow.setVisible(updated.energy() > 0);
    }

    if(current.energyCapacity() != updated.energyCapacity()) {

        //
        // The extension size is based on its energy capacity so if this changes
        // we need to notify the scene that the graphics item bounds are about to change
        //

        prepareGeometryChange();

        _extensionRenderer.setEnergyCapacity(updated.energyCapacity());
    }

    return _extensionRenderer.isDirty();
}
