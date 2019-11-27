/*
 * File: NukerRenderer.cpp
 * Created: 2019-1-23
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

#include "NukerRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NukerRenderer
// Utility class to draw the "Nuker" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NukerRenderer::NukerRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _resources(0),
      _energyCapacity(0),
      _resourceCapacity(0) {

}

NukerRenderer::~NukerRenderer() {

}

void NukerRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void NukerRenderer::setResources(int resources) {
    _resources = resources;
    setDirty(true);
}

void NukerRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

void NukerRenderer::setResourceCapacity(int resourceCapacity) {
    _resourceCapacity = resourceCapacity;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF NukerRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width, height);
}

void NukerRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const qreal borderPenWidth = scaledWidth(bounds.size(), BORDER_PEN_WIDTH_SCALE);
    const QRectF resourceBarRect = resourceStoreRect(bounds);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(playerColor (), borderPenWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(paletteColor(Color_Black));
    painter->drawPath(basePath(bounds));

    painter->setPen(Qt::NoPen);

    if(_energy < _energyCapacity) {
        painter->setBrush(paletteColor(Color_EnergyStore));
        painter->drawPath(energyStorePath(bounds));
    }

    if(_resources < _resourceCapacity) {
        painter->setBrush (paletteColor(Color_EnergyStore));
        painter->drawRect(resourceBarRect);
    }

    if(_energy > 0 && _energy <= _energyCapacity) {
        QRectF energyRect = scaledRect(bounds, _energy / _energyCapacity);

        painter->setBrush(paletteColor(Color_Energy));
        painter->drawPath(energyStorePath(energyRect));
    }

    if(_resources > 0 && _resources <= _resourceCapacity) {
        QRectF resourceRect(resourceBarRect);

        resourceRect.setWidth(resourceBarRect.width () * (_resources / _resourceCapacity));
        resourceRect.moveCenter(resourceBarRect.center());

        painter->setBrush(paletteColor(Color_Stored_Resource));
        painter->drawRect(resourceRect);
    }

    setDirty(false);
}

QImage NukerRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    NukerRenderer renderer;

    renderer.setEnergy(700);
    renderer.setEnergyCapacity(1000);

    renderer.setResources(500);
    renderer.setResourceCapacity(1000);

    return renderer.drawImage(size, fillColor, border);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPainterPath NukerRenderer::basePath(const QRectF& rect) const {
    const qreal resourceBarHeight = scaledHeight(rect.size(), RESOURCE_STORE_HEIGHT_SCALE);
    QPainterPath path;

    path.moveTo(rect.center().x(), rect.top());
    path.lineTo(rect.left(), rect.bottom() - resourceBarHeight);
    path.lineTo(rect.bottomLeft());
    path.lineTo(rect.bottomRight());
    path.lineTo(rect.right(), rect.bottom() - resourceBarHeight);
    path.closeSubpath();

    return path;
}

QPainterPath NukerRenderer::energyStorePath(const QRectF& rect) const {
    const qreal resourceBarHeight = scaledHeight(rect.size(), RESOURCE_STORE_HEIGHT_SCALE);
    const qreal energyStorePadding = scaledWidth (rect.size(), ENERGY_STORE_PADDING_SCALE);
    QPainterPath path;

    path.moveTo(rect.center().x(), rect.top() + (energyStorePadding * 2));
    path.lineTo(rect.left() + energyStorePadding, rect.bottom() - resourceBarHeight);
    path.lineTo(rect.right() - energyStorePadding, rect.bottom() - resourceBarHeight);
    path.closeSubpath();

    return path;
}

QRectF NukerRenderer::resourceStoreRect(const QRectF& rect) const {
    const qreal resourceStoreHeight = scaledHeight(rect.size (), RESOURCE_STORE_HEIGHT_SCALE);
    const qreal resourceStoreBarHeight = scaledHeight (rect.size (), RESROUCE_STORE_BAR_HEIGHT_SCALE);
    const qreal energyStorePadding = scaledWidth (rect.size(), ENERGY_STORE_PADDING_SCALE);
    QRectF rc = QRectF(0, 0, rect.width () - (energyStorePadding * 2), resourceStoreBarHeight);

    qreal cx = rect.center().x();
    qreal cy = (rect.bottom() - resourceStoreHeight) + (resourceStoreHeight / 2);

    rc.moveCenter(QPoint(cx, cy));

    return rc;
}
