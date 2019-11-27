/*
 * File: EnergyRenderer.cpp
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
#include <QPainterPath>

#include "EnergyRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EnergyRenderer
// Utility class to draw the "dropped energy" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EnergyRenderer::EnergyRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _energyCapacity(0) {

}

EnergyRenderer::~EnergyRenderer() {

}

void EnergyRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void EnergyRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF EnergyRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width, height);
}

void EnergyRenderer::draw(QPainter* painter, const QRectF& bounds) const {

    if(_energy > 0 && _energy <= _energyCapacity) {
        const QRectF energyRect = scaledRect(bounds, _energy / _energyCapacity);

        painter->setPen(Qt::NoPen);
        painter->setBrush(paletteColor(Color_Energy));
        painter->drawEllipse(energyRect);
    }

    setDirty(false);
}
