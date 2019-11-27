/*
 * File: UnknownRenderer.cpp
 * Created: 2018-12-28
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

#include "UnknownRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UnknownRenderer
// Utility class to draw a placeholder for unknown game entities. Used for debugging purposes during development
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UnknownRenderer::UnknownRenderer(QObject* parent /* = nullptr */)
    : _super(parent) {

}

UnknownRenderer::~UnknownRenderer() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF UnknownRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void UnknownRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const QFont serifFont("Monospace", scaledWidth(bounds.size(), FONT_SIZE_SCALE));

    painter->setBrush(Qt::darkGreen);
    painter->setPen(QPen(Qt::black, BORDER_PEN_WIDTH));
    painter->drawRoundRect(bounds, 70, 70);

    painter->setFont(serifFont);
    painter->drawText(bounds, Qt::AlignCenter, "?");
}
