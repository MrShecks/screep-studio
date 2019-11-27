/*
 * File: ContainerRenderer.cpp
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

#include "ContainerRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ContainerRenderer
// Utility class to draw the "Container" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ContainerRenderer::ContainerRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _power(0),
      _totalResources(0),
      _resourceCapacity(0) {

}

ContainerRenderer::~ContainerRenderer() {

}

void ContainerRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void ContainerRenderer::setPower(int power) {
    _power = power;
    setDirty(true);
}

void ContainerRenderer::setTotalResources(int totalResources) {
    _totalResources = totalResources;
    setDirty(true);
}

void ContainerRenderer::setResourceCapacity(int resourceCapacity) {
    _resourceCapacity = resourceCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF ContainerRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void ContainerRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const QRectF energyStoreRect = scaledRect (bounds, ENERGY_STORE_SIZE);

    painter->setPen(QPen(paletteColor(Color_Black), BORDER_PEN_WIDTH, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter->setBrush(paletteColor(Color_EnergyStore));

    painter->drawRect(bounds);

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

QImage ContainerRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    ContainerRenderer renderer;

    renderer.setEnergy(600);
    renderer.setPower(0);
    renderer.setTotalResources(0);
    renderer.setResourceCapacity(1000);

    return renderer.drawImage(size, fillColor, border);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ContainerRenderer::drawResourceBar(QPainter* painter, const QRectF& rect, qreal resources, const QColor& color) const {
    QRectF resourceRect(0, 0, rect.width(), qMin(rect.height(), rect.height()* (resources / _resourceCapacity)));

    resourceRect.moveBottomLeft(rect.bottomLeft());
    painter->setBrush(color);
    painter->drawRect(resourceRect);
}
