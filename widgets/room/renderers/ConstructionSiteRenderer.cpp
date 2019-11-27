/*
 * File: ConstructionSiteRenderer.cpp
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

#include "ConstructionSiteRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConstructionSiteRenderer
// Utility class to draw a the "construction site" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ConstructionSiteRenderer::ConstructionSiteRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _progress(0),
      _progressTotal(0) {

}

ConstructionSiteRenderer::~ConstructionSiteRenderer() {

}

void ConstructionSiteRenderer::setProgress(int progress, int progressTotal) {
    _progress = progress;
    _progressTotal = progressTotal;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF ConstructionSiteRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSizeF(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void ConstructionSiteRenderer::draw(QPainter* painter, const QRectF& bounds) const {

    painter->setPen(QPen(playerColor(), BORDER_PEN_WIDTH));
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(bounds);

    int spanAngle = -(360 * (_progress / _progressTotal));

    painter->setPen(Qt::NoPen);
    painter->setBrush(playerColor());
    painter->drawPie (bounds, 90 * 16, spanAngle * 16);

    setDirty(false);
}
