/*
 * File: LabRenderer.cpp
 * Created: 2019-1-22
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

#include "LabRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LabRenderer
// Utility class to draw the "Lab" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LabRenderer::LabRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _energyCapacity(0) {

}

LabRenderer::~LabRenderer() {

}

void LabRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void LabRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF LabRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width, height);
}

void LabRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const qreal borderPenWidth = scaledWidth(bounds.size(), BORDER_PEN_WIDTH_SCALE);
    const QRectF energyStoreBarRect = energyStoreRect(bounds, borderPenWidth);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(playerColor (), borderPenWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(paletteColor(Color_Black));
    painter->drawPath(basePath(bounds));

    painter->setPen(Qt::NoPen);
    painter->setBrush(paletteColor(Color_EnergyStore));
    painter->drawEllipse(scaledRect (bounds, RESOURCE_STORE_SIZE_SCALE));

    painter->setPen(QPen(paletteColor(Color_Black), borderPenWidth));

    if(_energy < _energyCapacity) {
        painter->setBrush(paletteColor(Color_EnergyStore));
        painter->drawRect(energyStoreBarRect);
    }

    if(_energy > 0 && _energy <= _energyCapacity) {
        QRectF energyRect(energyStoreBarRect);

        energyRect.setWidth(energyStoreBarRect.width() * (_energy / _energyCapacity));
        energyRect.moveCenter(energyStoreBarRect.center());

        painter->setBrush(paletteColor(Color_Energy));
        painter->drawRect(energyRect);
    }

    setDirty(false);
}

QImage LabRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    LabRenderer renderer;

    renderer.setEnergy(700);
    renderer.setEnergyCapacity(1000);

    return renderer.drawImage(size, fillColor, border);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPainterPath LabRenderer::basePath(const QRectF& rect) const {
    QPainterPath path;

    path.arcMoveTo(rect, -30);
    path.arcTo(rect, -30, 180+60);
    path.lineTo(rect.bottomLeft());
    path.lineTo(rect.bottomRight());
    path.closeSubpath ();

    return path;
}

QRectF LabRenderer::energyStoreRect(const QRectF& rect, qreal borderPenWidth) const {
    const qreal resourceStoreBarHeight = scaledHeight (rect.size (), ENERGY_BAR_HEIGHT_SCALE);
    QRectF rc = scaledRect(rect, ENERGY_STORE_SIZE_SCALE);

    rc.setHeight(resourceStoreBarHeight);
    rc.moveBottom(rect.bottom () - borderPenWidth);

    return rc;
}
