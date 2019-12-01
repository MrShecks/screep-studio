/*
 * File: RoomGraphicsItemTerminal.cpp
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

#include "RoomGraphicsItemTerminal.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemTerminal
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemTerminal::RoomGraphicsItemTerminal(const TerminalEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Terminal, entity, cellSize, ItemZOrder_Terminal, parent),
      _terminalRenderer(this),
      _glow(this) {

    const int totalResources = entity.getTotalResources();

    _terminalRenderer.setPower(entity.power());
    _terminalRenderer.setEnergy(entity.energy());
    _terminalRenderer.setTotalResources(totalResources);
    _terminalRenderer.setResourceCapacity(entity.energyCapacity());

    _glow.setScale(GLOW_EFFECT_SCALE);
    _glow.setOpacity(GLOW_EFFECT_OPACITY);
    _glow.setVisible(totalResources > 0);

}

RoomGraphicsItemTerminal::~RoomGraphicsItemTerminal() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemTerminal::itemSize(const QSize& cellSize) const {
    return _terminalRenderer.size(cellSize);
}

void RoomGraphicsItemTerminal::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _terminalRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemTerminal::beginUpdate(const TerminalEntity& current, const TerminalEntity& updated) {

    if(current.energy() != updated.energy())
        _terminalRenderer.setEnergy(updated.energy());

    if(current.power()!= updated.power())
        _terminalRenderer.setPower(updated.power());

    const int currentTotalResources = current.getTotalResources();
    const int updatedTotalResources = updated.getTotalResources();

    if(currentTotalResources != updatedTotalResources)
        _terminalRenderer.setTotalResources(updatedTotalResources);

    if(current.energyCapacity()!= updated.energyCapacity())
        _terminalRenderer.setResourceCapacity(updated.energyCapacity());

    if(_terminalRenderer.isDirty())
        _glow.setVisible(updatedTotalResources > 0);

    return _terminalRenderer.isDirty();
}
