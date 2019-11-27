/*
 * File: PowerSpawnRenderer.cpp
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

#include "PowerSpawnRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PowerSpawnRenderer
// Utility class to draw the "Power Spawn" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PowerSpawnRenderer::PowerSpawnRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _power(0),
      _energyCapacity(0),
      _powerCapacity(0) {

}

PowerSpawnRenderer::~PowerSpawnRenderer() {

}

void PowerSpawnRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void PowerSpawnRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

void PowerSpawnRenderer::setPower(int power) {
    _power = power;
    setDirty(true);
}

void PowerSpawnRenderer::setPowerCapacity(int powerCapacity) {
    _powerCapacity = powerCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF PowerSpawnRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSizeF(width, height);
}

void PowerSpawnRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const QRectF energyStoreRect = scaledRect(bounds, ENERGY_STORE_SCALE);
    const qreal basePenWidth = scaledWidth(bounds.size(), BORDER_PEN_SCALE);
    const qreal corePenWidth = scaledWidth(bounds.size(), INNER_CORE_PEN_SCALE);

    painter->setBrush(paletteColor(Color_PowerSpawn_Base));
    painter->setPen(QPen(paletteColor(Color_PowerSpawn_Outer_Border), basePenWidth));
    painter->drawEllipse(bounds);

    painter->setPen(QPen(paletteColor(Color_PowerSpawn_Inner_Border), corePenWidth));
    painter->drawEllipse(scaledRect(bounds, INNER_CORE_SCALE));

    painter->setPen(Qt::NoPen);

    if(_energy < _energyCapacity) {
        painter->setBrush(paletteColor(Color_EnergyStore));
        painter->drawEllipse(energyStoreRect);
    }

    if(_energy > 0 && _energy <= _energyCapacity) {
        QRectF energyRect = scaledRect(energyStoreRect, _energy / _energyCapacity);

        painter->setBrush(paletteColor(Color_Energy));
        painter->drawEllipse(energyRect);
    }

    if(_power > 0 && _power <= _powerCapacity) {
        const qreal progressPenWidth = scaledWidth (bounds.size(), PROGRESS_PEN_SCALE);
        const qreal powerPercent = (_power / _powerCapacity) * 360;
        const QRectF progressRect = scaledRect(bounds, POWER_PROGRESS_SCALE);

        painter->setPen(QPen(paletteColor(Color_PowerSpawn_Progress), progressPenWidth, Qt::SolidLine, Qt::FlatCap));
        painter->drawArc(progressRect, 90 * 16, -(powerPercent * 16));
    }

    setDirty(false);
}

QImage PowerSpawnRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    PowerSpawnRenderer renderer;

    renderer.setEnergy(50);
    renderer.setEnergyCapacity(100);

    renderer.setPower(75);
    renderer.setPowerCapacity(100);

    return renderer.drawImage(size, fillColor, border);
}

