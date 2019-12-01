/*
 * File: TerminalRenderer.cpp
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
#include <QtMath>

#include "TerminalRenderer.h"
#include "utils/PaintUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TerminalRenderer
// Utility class to draw the "Terminal" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TerminalRenderer::TerminalRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _power(0),
      _energy(0),
      _totalResources(0),
      _resourceCapacity(0) {

}

TerminalRenderer::~TerminalRenderer() {

}

void TerminalRenderer::setPower(int power) {
    _power = power;
    setDirty(true);
}

void TerminalRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void TerminalRenderer::setTotalResources(int resources) {
    _totalResources = resources;
    setDirty(true);
}

void TerminalRenderer::setResourceCapacity(int resourceCapacity) {
    _resourceCapacity = resourceCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF TerminalRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width, height);
}

void TerminalRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const qreal borderPenWidth = scaledWidth(bounds.size(), BORDER_PEN_WIDTH_SCALE);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(playerColor(), borderPenWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(paletteColor(Color_Black));

    painter->translate(bounds.center());
    painter->rotate(45.0f / 2);
    painter->drawPath(PaintUtils::octagonalPath(bounds));

    painter->setPen(Qt::NoPen);
    painter->setBrush(paletteColor(Color_Gray));
    painter->drawPath(PaintUtils::octagonalPath(scaledRect(bounds, ARROW_SIZE_SCALE)));

    painter->rotate(-(45.0f / 2));
    painter->translate(-bounds.center());

    const QRectF energyStoreRect = scaledRect(bounds, ENERGY_STORE_SIZE_SCALE);

    painter->setPen(QPen(paletteColor(Color_Black), borderPenWidth));
    painter->setBrush(paletteColor(Color_EnergyStore));
    painter->drawRect(energyStoreRect);

    painter->setPen(Qt::NoPen);

    // This probably not the most efficient way to draw the energy bars but it's the
    // method used by the official Screeps opensource renderer code.

    if(_power + _energy < _totalResources) {
        painter->setBrush(paletteColor(Color_Stored_Resource));
        painter->drawRect(scaledRect(energyStoreRect, _totalResources / _resourceCapacity));
    }

    if(_power > 0) {
        painter->setBrush(paletteColor(Color_Stored_Power));
        painter->drawRect(scaledRect(energyStoreRect, (_power + _energy) / _resourceCapacity));
    }

    if(_energy > 0) {
        painter->setBrush(paletteColor(Color_Energy));
        painter->drawRect(scaledRect(energyStoreRect, _energy / _resourceCapacity));
    }

    setDirty(false);
}

QImage TerminalRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    TerminalRenderer renderer;

    renderer.setEnergy(300);
    renderer.setTotalResources(500);
    renderer.setResourceCapacity(1000);

    return renderer.drawImage(size, fillColor, border);
}
