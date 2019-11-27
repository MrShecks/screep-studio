/*
 * File: ControllerRenderer.cpp
 * Created: 2019-1-5
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

#include "ScreepsApi.h"
#include "ControllerRenderer.h"
#include "utils/PaintUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ControllerRenderer
// Utility class to draw the "Room Controller" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ControllerRenderer::ControllerRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _controllerLevel(0) {

}

ControllerRenderer::~ControllerRenderer() {

}

void ControllerRenderer::setLevel(int controllerLevel) {
    Q_ASSERT(controllerLevel >= 0 && controllerLevel <= Screeps::MAX_CONTROLLER_LEVEL);

    _controllerLevel = controllerLevel;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF ControllerRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSizeF(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void ControllerRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const QPainterPath controllerBase = PaintUtils::octagonalPath(bounds).translated(bounds.center());

    painter->setPen(QPen(Qt::gray, BORDER_PEN_WIDTH));
    painter->setBrush(paletteColor(Color_Controller_Base));
    painter->drawPath(controllerBase);

    if(_controllerLevel > 0) {
        const QRectF progressRect = scaledRect(bounds, PROGRESS_SIZE_SCALE);
        const qreal segmentSize = (360.0f / Screeps::MAX_CONTROLLER_LEVEL) - SEGMENT_SPACING;
        qreal startAngle = 90;

        painter->setPen(QPen(paletteColor(Color_Controller_Level_Segment), SEGMENT_PEN_WIDTH, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));

        for(int n = 0; n < _controllerLevel; ++n) {
            painter->drawArc(progressRect, startAngle * 16, -(segmentSize * 16));
            startAngle -= SEGMENT_SPACING + segmentSize;
        }
    }

    painter->setPen(playerColor());
    painter->drawText(bounds, Qt::AlignCenter, QString::number(_controllerLevel));

    setDirty(false);
}
