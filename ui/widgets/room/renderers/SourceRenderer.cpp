/*
 * File: SourceRenderer.cpp
 * Created: 2019-1-1
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

#include "SourceRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SourceRenderer
// Utility class to draw a the "energy source" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SourceRenderer::SourceRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _energyCapacity(0) {

}

SourceRenderer::~SourceRenderer() {

}

void SourceRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void SourceRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF SourceRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void SourceRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const qreal scale = SOURCE_MIN_SIZE + ((100 - SOURCE_MIN_SIZE) * (_energy / _energyCapacity));
    const QRectF sourceRect = scaledRect(bounds, scale / 100);

    painter->setBrush(paletteColor(Color_Energy));
    painter->setPen(QPen(paletteColor(Color_EnergyStore), BORDER_PEN_WIDTH));
    painter->drawRoundRect(sourceRect);

    setDirty(false);
}
