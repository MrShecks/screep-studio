/*
 * File: ExtensionRenderer.cpp
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

#include "ExtensionRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ExtensionRenderer
// Utility class to draw the "Extension" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ExtensionRenderer::ExtensionRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _energyCapacity(0) {

}

ExtensionRenderer::~ExtensionRenderer() {

}

void ExtensionRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void ExtensionRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF ExtensionRenderer::size(const QSize& cellSize) const {
    const int size = getExtensionSize(_energyCapacity);
    const qreal width = scaledWidth(cellSize, size);
    const qreal height = scaledHeight(cellSize, size);

    return QSizeF(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void ExtensionRenderer::draw(QPainter* painter, const QRectF& bounds) const {

    painter->setBrush(paletteColor(Color_Black));
    painter->setPen(QPen(playerColor(), BORDER_PEN_WIDTH));
    painter->drawEllipse(bounds);

    if(_energyCapacity > 0) {
        const QRectF energyStoreRect = scaledRect(bounds, ENERGY_STORE_SIZE);

        painter->setPen(Qt::NoPen);

        if(_energy < _energyCapacity) {
            painter->setBrush(paletteColor(Color_EnergyStore));
            painter->drawEllipse(energyStoreRect);
        }

        if(_energy) {
            const QRectF energyRect = scaledRect(energyStoreRect, _energy / _energyCapacity);

            painter->setBrush(paletteColor(Color_Energy));
            painter->drawEllipse(energyRect);
        }
    }

    setDirty(false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QImage ExtensionRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    ExtensionRenderer renderer;

    renderer.setEnergy(40);
    renderer.setEnergyCapacity(50);

    return renderer.drawImage (size, fillColor, border);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ExtensionRenderer::getExtensionSize(int energyCapacity) const {
    int size;

    if(energyCapacity >= 200)
        size = LARGE_ENTITY_SIZE;
    else if(energyCapacity >= 100)
        size = MEDIUM_ENTITY_SIZE;
    else
        size = SMALL_ENTITY_SIZE;

    return size;
}
