/*
 * File: LinkRenderer.cpp
 * Created: 2019-1-15
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

#include "LinkRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LinkRenderer
// Utility class to draw the "Link" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LinkRenderer::LinkRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _energyCapacity(0) {

}

LinkRenderer::~LinkRenderer() {

}

void LinkRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void LinkRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF LinkRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void LinkRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    QRectF energyStoreRect = scaledRect(bounds, ENERGY_STORE_SIZE_SCALE);

    painter->setPen(QPen(playerColor(), BORDER_PEN_WIDTH, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(paletteColor(Color_Black));

    QPainterPath base = basePath(bounds);
    painter->drawPath(base);

//    _energy = 500;
//    _energyCapacity = 1000;

    painter->setPen(QPen(paletteColor(Color_Black), BORDER_PEN_WIDTH, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(paletteColor(Color_EnergyStore));

    painter->drawPath(basePath(energyStoreRect));

    if(_energy > 0 && _energy <= _energyCapacity) {
        const QRectF energyRect = scaledRect(energyStoreRect, _energy / _energyCapacity);

        painter->setPen(Qt::NoPen);
        painter->setBrush(paletteColor(Color_Energy));
        painter->drawPath(basePath(energyRect));
    }

    setDirty(false);
}

QImage LinkRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    LinkRenderer renderer;

    renderer.setEnergy(800);
    renderer.setEnergyCapacity(1000);

    return renderer.drawImage(size, fillColor, border);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPainterPath LinkRenderer::basePath(const QRectF &rect) const {
    QPainterPath path;

    path.moveTo(rect.center().x(), rect.top());
    path.lineTo(rect.right(), rect.center ().y());
    path.lineTo(rect.center().x(), rect.bottom());
    path.lineTo(rect.left(), rect.center().y());
    path.closeSubpath();

    return path;
}
