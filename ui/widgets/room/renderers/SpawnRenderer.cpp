/*
 * File: SpawnRenderer.cpp
 * Created: 2018-12-27
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

#include "SpawnRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SpawnRenderer
// Utility class to draw the "Spawn" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SpawnRenderer::SpawnRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _energyCapacity(0),
      _elapsedSpawnTime(0),
      _totalSpawnTime(0) {

}

SpawnRenderer::~SpawnRenderer() {

}

void SpawnRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void SpawnRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

void SpawnRenderer::setSpawnProgress(int elapsedSpawnTime, int totalSpawnTime) {
    _elapsedSpawnTime = elapsedSpawnTime;
    _totalSpawnTime = totalSpawnTime;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF SpawnRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSizeF(width, height);
}

void SpawnRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const QRectF energyStoreRect = scaledRect(bounds, ENERGY_STORE_SCALE);
    const qreal basePenWidth = scaledWidth(bounds.size(), BORDER_PEN_SCALE);

    painter->setBrush(paletteColor(Color_Spawn_Base));
    painter->setPen(QPen(paletteColor(Color_Gray), basePenWidth));
    painter->drawEllipse(bounds);

    painter->setPen(Qt::NoPen);

    if(_energy < _energyCapacity) {
        painter->setBrush(paletteColor(Color_EnergyStore));
        painter->drawEllipse(energyStoreRect);
    }

    if(_energy > 0 && _energy <= _energyCapacity) {
        const QRectF energyRect = scaledRect(energyStoreRect, _energy / _energyCapacity);

        painter->setBrush(paletteColor(Color_Energy));
        painter->drawEllipse(energyRect);
    }

    if(_elapsedSpawnTime > 0 && _elapsedSpawnTime <= _totalSpawnTime) {
        const qreal progresPenWidth = scaledWidth(bounds.size(), PROGRESS_PEN_SCALE);
        const qreal spawnPercent = (_elapsedSpawnTime / static_cast<qreal>(_totalSpawnTime)) * 360;
        const QRectF progressRect = scaledRect(bounds, SPAWN_PROGRESS_SCALE);

        painter->setPen(QPen(paletteColor(Color_Spawn_Progress), progresPenWidth, Qt::SolidLine, Qt::FlatCap));
        painter->drawArc(progressRect, 90 * 16, -(spawnPercent * 16));
    }

    setDirty(false);
}

QImage SpawnRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    SpawnRenderer renderer;

    renderer.setEnergy(80);
    renderer.setEnergyCapacity(100);
    renderer.setSpawnProgress(75, 100);

    return renderer.drawImage(size, fillColor, border);
}

//{
//    "_id": "5c219d266edd010419f53a3c",
//    "energy": 34,
//    "energyCapacity": 300,
//    "hits": 5000,
//    "hitsMax": 5000,
//    "name": "Spawn1",
//    "notifyWhenAttacked": true,
//    "off": false,
//    "room": "W8N3",
//    "spawning": {
//        "name": "h1",
//        "needTime": 60,
//        "remainingTime": 26
//    },
//    "type": "spawn",
//    "user": "5c219cbd6edd010419f53a3a",
//    "x": 16,
//    "y": 12
//}

