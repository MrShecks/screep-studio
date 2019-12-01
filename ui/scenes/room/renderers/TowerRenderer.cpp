/*
 * File: TowerRenderer.cpp
 * Created: 2018-12-29
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

#include "TowerRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TowerRenderer
// Utility class to draw the "Tower" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TowerRenderer::TowerRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _rotation(0),
      _energy(0),
      _energyCapacity(0) {

}

TowerRenderer::~TowerRenderer() {

}

qreal TowerRenderer::rotation() const {
    return _rotation;
}

void TowerRenderer::setRotation(qreal rotation) {
    _rotation = rotation;
}

void TowerRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void TowerRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF TowerRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void TowerRenderer::draw(QPainter* painter, const QRectF& bounds) const {

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->translate(bounds.center());
    painter->rotate (_rotation);

    QRectF towerBaseRect = scaledRect(bounds, TOWER_BASE_SIZE);

    towerBaseRect.translate(-bounds.center());

    painter->setPen(QPen(playerColor(), BORDER_PEN_WIDTH));
    painter->setBrush(paletteColor(Color_Tower_Base));
    painter->drawEllipse(towerBaseRect);

    QRectF energyStoreRect = scaledRect(bounds, ENERGY_STORE_WIDTH, ENERGY_STORE_HEIGHT);

    energyStoreRect.translate(-bounds.center());

    QRectF turretRect = scaledRect(bounds, TURRET_WIDTH, TURRET_HEIGHT);

    turretRect.moveBottomLeft(QPointF(-(turretRect.width () / 2), energyStoreRect.top ()));

    painter->setPen(QPen(paletteColor(Color_Black), BORDER_PEN_WIDTH));
    painter->setBrush(paletteColor(Color_Tower_Turret));

    painter->drawRect(turretRect);
    painter->setPen(Qt::NoPen);

    if(_energy < _energyCapacity) {
        painter->setBrush(paletteColor(Color_EnergyStore));
        painter->drawRoundRect (energyStoreRect);
    }

    if(_energy) {
        QRectF rect = scaledRect(energyStoreRect, 1.0, _energy / _energyCapacity);

        rect.moveBottomLeft(energyStoreRect.bottomLeft());

        painter->setBrush(paletteColor(Color_Energy));
        painter->drawRoundRect (rect);
    }

    setDirty(false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QImage TowerRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    TowerRenderer renderer;

    renderer.setRotation(45);
    renderer.setEnergy(800);
    renderer.setEnergyCapacity(1000);

    return renderer.drawImage(size, fillColor, border);
}

//
// Game.getObjectById('5c226e9dc7a8e50421aeffda').heal(Game.creeps.h2)
// Game.getObjectById('5c226e9dc7a8e50421aeffda').attack(Game.creeps.h2)
//{
//    "_id": "5c226e9dc7a8e50421aeffda",
//    "actionLog": {
//        "attack": null,
//        "heal": null,
//        "repair": null
//    },
//    "energy": 1000,
//    "energyCapacity": 1000,
//    "hits": 3000,
//    "hitsMax": 3000,
//    "notifyWhenAttacked": true,
//    "room": "W8N3",
//    "type": "tower",
//    "user": "5c219cbd6edd010419f53a3a",
//    "x": 21,
//    "y": 15
//}
//
