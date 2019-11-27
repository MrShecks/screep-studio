/*
 * File: TombstoneRenderer.cpp
 * Created: 2018-12-29
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
#include <QPainterPath>

#include "TombstoneRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TombstoneRenderer
// Utility class to draw the "Tombstone" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TombstoneRenderer::TombstoneRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _totalResources(0) {

}

TombstoneRenderer::~TombstoneRenderer() {

}

void TombstoneRenderer::setTotalResources(int totalResources) {
    _totalResources = totalResources;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF TombstoneRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void TombstoneRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const QFont symbolFont("Dinbats", scaledWidth(bounds.size(), FONT_SIZE_SCALE));
    QPainterPath path;

    path.moveTo(bounds.center());
    path.arcTo(bounds, 0, 180);
    path.lineTo(bounds.bottomLeft());
    path.lineTo(bounds.bottomRight());
    path.lineTo(bounds.right(), bounds.center().y());
    path.closeSubpath();

    //
    // TODO: Set opacity based on decayTime, deathTime and gameTime using the following
    //
    // Opacity = 1.0f - ((gameTime - deathTime) / (decayTime - deathTime))
    //

    painter->setOpacity(0.5);

    painter->setBrush(paletteColor(Color_Tombstone));
    painter->setPen(QPen(paletteColor(Color_Tombstone_Border), BORDER_PEN_WIDTH));
    painter->drawPath(path.simplified());

    painter->setFont(symbolFont);
    painter->setPen(_totalResources > 0 ? playerColor() : paletteColor(Color_Black));
    painter->drawText(bounds, Qt::AlignCenter, QChar(0x271D));

    setDirty(false);
}
