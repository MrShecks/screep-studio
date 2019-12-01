/*
 * File: RoomGraphicsItemSource.cpp
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

#include "RoomGraphicsItemSource.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemSource
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemSource::RoomGraphicsItemSource(const SourceEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Source, entity, cellSize, ItemZOrder_Source, parent),
      _sourceRenderer(this),
      _glow(this) {

    _sourceRenderer.setEnergy(entity.energy());
    _sourceRenderer.setEnergyCapacity(entity.energyCapacity());

    _glow.setScale(GLOW_EFFECT_SCALE);
    _glow.setGlowAnimation(GLOW_EFFECT_OPACITY_MIN, GLOW_EFFECT_OPACITY_MAX, 5000);
}

RoomGraphicsItemSource::~RoomGraphicsItemSource() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemSource::itemSize(const QSize& cellSize) const {
    return _sourceRenderer.size(cellSize);
}

void RoomGraphicsItemSource::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _sourceRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemSource::beginUpdate(const SourceEntity& current, const SourceEntity& updated) {

    if(current.energy() != updated.energy())
        _sourceRenderer.setEnergy(updated.energy());

    if(current.energyCapacity() != updated.energyCapacity())
        _sourceRenderer.setEnergyCapacity(updated.energyCapacity());

    return _sourceRenderer.isDirty();
}

