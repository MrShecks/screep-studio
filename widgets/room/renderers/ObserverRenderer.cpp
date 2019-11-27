/*
 * File: ObserverRenderer.cpp
 * Created: 2019-2-1
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

#include "ObserverRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ObserverRenderer
// Utility class to draw the "Observer" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ObserverRenderer::ObserverRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _eyeRotation(0) {

}

ObserverRenderer::~ObserverRenderer() {

}

qreal ObserverRenderer::eyeRotation() const {
    return _eyeRotation;
}

void ObserverRenderer::setEyeRotation(qreal eyeRotation) {
    _eyeRotation = eyeRotation;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF ObserverRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width, height);
}

void ObserverRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const qreal borderPenWidth = scaledWidth (bounds.size(), BORDER_PEN_SCALE);
    const qreal eyeRadius = scaledWidth(bounds.size(), EYE_RADIUS_SCALE);
    const QRectF baseRect = scaledRect(bounds, BASE_WIDTH_SCALE, BASE_HEIGHT_SCALE);

    painter->setPen(QPen(playerColor(), borderPenWidth));
    painter->setBrush(paletteColor(Color_Observer_Base));
    painter->drawEllipse(baseRect);

    const qreal angle = qDegreesToRadians(_eyeRotation);
    const qreal x = ((baseRect.width() / 2) - eyeRadius - borderPenWidth) * qCos(angle);
    const qreal y = ((baseRect.height() / 2) - eyeRadius - borderPenWidth) * qSin(angle);

    painter->setPen(Qt::NoPen);
    painter->setBrush(playerColor());
    painter->drawEllipse(baseRect.center() + QPointF(x, y), eyeRadius, eyeRadius);

    setDirty(false);
}

QImage ObserverRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    ObserverRenderer renderer;

    renderer.setOwner (EntityRenderer::OwnerType_Player);
    renderer.setEyeRotation(45);

    return renderer.drawImage(size, fillColor, border);
}
