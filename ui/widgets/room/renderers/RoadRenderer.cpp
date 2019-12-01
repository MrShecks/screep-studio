/*
 * File: RoadRenderer.cpp
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
#include <QVector>

#include "RoadRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoadRenderer
// Utility class to draw the "road" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoadRenderer::RoadRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _neighbours(RoomUtils::NeighbourFlag_None) {

}

RoadRenderer::~RoadRenderer() {

}

void RoadRenderer::setNeighbours(RoomUtils::NeighbourFlags neighbours) {
    _neighbours = neighbours;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoadRenderer::size(const QSize& cellSize) const {
    return QSize(cellSize.width() + (PEN_WIDTH / 2), cellSize.height() + (PEN_WIDTH / 2));
}

void RoadRenderer::draw(QPainter* painter, const QRectF& bounds) const {

    painter->setPen(QPen(paletteColor(Color_Road), PEN_WIDTH, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    //_neighbours = RoomUtils::NeighbourFlag_All;

    if(_neighbours == RoomUtils::NeighbourFlag_None) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(paletteColor(Color_Road));
        painter->drawEllipse(bounds.center (), PEN_WIDTH / 2, PEN_WIDTH / 2);
    }
    else {
        QVector<QLineF> lines;

        if(_neighbours & RoomUtils::NeighbourFlag_North)
            lines.append(QLineF(bounds.center(), QPointF(bounds.center().x(), bounds.top())));

        if(_neighbours & RoomUtils::NeighbourFlag_NorthEast)
            lines.append(QLineF(bounds.center(), bounds.topRight()));

        if(_neighbours & RoomUtils::NeighbourFlag_East)
            lines.append(QLineF(bounds.center(), QPointF(bounds.right(), bounds.center ().y())));

        if(_neighbours & RoomUtils::NeighbourFlag_SouthEast)
            lines.append(QLineF(bounds.center(), bounds.bottomRight()));

        if(_neighbours & RoomUtils::NeighbourFlag_South)
            lines.append(QLineF(bounds.center(), QPointF(bounds.center().x(), bounds.bottom())));

        if(_neighbours & RoomUtils::NeighbourFlag_SouthWest)
            lines.append(QLineF(bounds.center(), bounds.bottomLeft()));

        if(_neighbours & RoomUtils::NeighbourFlag_West)
            lines.append(QLineF(bounds.center(), QPointF(bounds.left(), bounds.center ().y())));

        if(_neighbours & RoomUtils::NeighbourFlag_NorthWest)
            lines.append(QLineF(bounds.center(), bounds.topLeft()));

        painter->drawLines(lines);
    }

    setDirty(false);
}

QImage RoadRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    RoadRenderer renderer;

    renderer.setNeighbours(RoomUtils::NeighbourFlag_North | RoomUtils::NeighbourFlag_South | RoomUtils::NeighbourFlag_West);

    return renderer.drawImage(size, fillColor, border);

}
