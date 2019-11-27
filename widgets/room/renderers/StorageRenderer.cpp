/*
 * File: StorageRenderer.cpp
 * Created: 2019-1-2
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

#include "StorageRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StorageRenderer
// Utility class to draw the "Storage" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StorageRenderer::StorageRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _power(0),
      _energy(0),
      _totalResources(0) {

}

StorageRenderer::~StorageRenderer() {

}

void StorageRenderer::setPower(int power) {
    _power = power;
    setDirty(true);
}

void StorageRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void StorageRenderer::setTotalResources(int resources) {
    _totalResources = resources;
    setDirty(true);
}

void StorageRenderer::setResourceCapacity(int resourceCapacity) {
    _resourceCapacity = resourceCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF StorageRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSizeF(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void StorageRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const QRectF energyStoreRect = scaledRect (bounds, ENERGY_STORE_SIZE_SCALE);

    painter->setBrush(paletteColor(Color_Black));
    painter->setPen(QPen(playerColor(), BORDER_PEN_WIDTH));
    painter->drawRoundRect(bounds);

    painter->setPen(Qt::NoPen);
    painter->setBrush(paletteColor(Color_EnergyStore));
    painter->drawRect(energyStoreRect);

    painter->setPen(Qt::NoPen);

    // This probably not the most efficient way to draw the energy bars but it's the
    // method used by the official Screeps opensource renderer code.

    if(_power + _energy < _totalResources) {
        drawResourceBar(painter, energyStoreRect, _totalResources, paletteColor(Color_Stored_Resource));
    }

    if(_power > 0) {
        drawResourceBar(painter, energyStoreRect, _power + _energy, paletteColor(Color_Stored_Power));
    }

    if(_energy > 0) {
        drawResourceBar(painter, energyStoreRect, _energy, paletteColor(Color_Energy));
    }

    setDirty(false);
}

QImage StorageRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    StorageRenderer renderer;

    renderer.setEnergy(5000);
    renderer.setPower(1000);
    renderer.setTotalResources(2000);
    renderer.setResourceCapacity(10000);

    return renderer.drawImage(size, fillColor, border);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void StorageRenderer::drawResourceBar(QPainter* painter, const QRectF& rect, qreal resources, const QColor& color) const {
    QRectF resourceRect(0, 0, rect.width(), qMin(rect.height(), rect.height() * (resources / _resourceCapacity)));

    resourceRect.moveBottomLeft(rect.bottomLeft());
    painter->setBrush(color);
    painter->drawRect(resourceRect);
}

//{
//    "G": 0,
//    "GH": 6590,
//    "GH2O": 0,
//    "GHO2": 0,
//    "GO": 0,
//    "H": 0,
//    "K": 0,
//    "KH": 0,
//    "KH2O": 0,
//    "KHO2": 9485,
//    "KO": 2820,
//    "L": 35857,
//    "LH": 0,
//    "LH2O": 0,
//    "LHO2": 0,
//    "LO": 0,
//    "O": 80,
//    "OH": 0,
//    "U": 0,
//    "UH": 77,
//    "UH2O": 2920,
//    "UHO2": 0,
//    "UL": 2820,
//    "UO": 0,
//    "X": 0,
//    "XGH2O": 0,
//    "XGHO2": 0,
//    "XKH2O": 0,
//    "XKHO2": 10850,
//    "XLH2O": 360,
//    "XLHO2": 0,
//    "XUH2O": 0,
//    "XUHO2": 0,
//    "XZH2O": 2050,
//    "XZHO2": 0,
//    "Z": 0,
//    "ZH": 322,
//    "ZH2O": 0,
//    "ZHO2": 0,
//    "ZK": 2560,
//    "ZO": 0,
//    "_id": "5bad32b09dca93647d1bb261",
//    "energy": 499372,
//    "energyCapacity": 1000000,
//    "hits": 10000,
//    "hitsMax": 10000,
//    "notifyWhenAttacked": true,
//    "power": 0,
//    "room": "W19S47",
//    "type": "storage",
//    "user": "5b1d1c9e340d195a66436301",
//    "x": 27,
//    "y": 34
//}
