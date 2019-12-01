/*
 * File: ExtractorRenderer.cpp
 * Created: 2019-1-9
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

#include "ExtractorRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ExtractorRenderer
// Utility class to draw the "Extractor" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ExtractorRenderer::ExtractorRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _rotation(0) {

}

ExtractorRenderer::~ExtractorRenderer() {

}

qreal ExtractorRenderer::rotation() const {
    return _rotation;
}

void ExtractorRenderer::setRotation(qreal rotation) {
    _rotation = rotation;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF ExtractorRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width, height);
}

void ExtractorRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const qreal arcHeight = (bounds.width() / 100.0f) * EXTRACTOR_ARC_SIZE_SCALE;

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->translate(bounds.center());
    painter->rotate(_rotation);
    painter->setOpacity(0.5);

    painter->setPen(QPen(playerColor(), arcHeight, Qt::SolidLine, Qt::FlatCap));

    const QRectF extractorRect = bounds.translated (-bounds.center());

    drawArc(painter, extractorRect, 30, EXTRACTOR_ARC_WIDTH);
    drawArc(painter, extractorRect, -90, EXTRACTOR_ARC_WIDTH);
    drawArc(painter, extractorRect, -210, EXTRACTOR_ARC_WIDTH);

    setDirty(false);
}

QImage ExtractorRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    ExtractorRenderer renderer;

    renderer.setOwner(ExtractorRenderer::OwnerType_Player);

    return renderer.drawImage(size, fillColor, border);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ExtractorRenderer::drawArc(QPainter* painter, const QRectF& rect, qreal startAngle, qreal size) const {
    painter->drawArc(rect, (startAngle + 90) * 16, -(size * 16));
}
