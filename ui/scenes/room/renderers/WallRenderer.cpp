/*
 * File: WallRenderer.cpp
 * Created: 2019-1-27
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
#include <QPainterPathStroker>

#include "WallRenderer.h"
#include "utils/PaintUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WallRenderer
// Utility class to draw the "Constructed Wall" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WallRenderer::WallRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _neighbours(RoomUtils::NeighbourFlag_None) {

}

WallRenderer::~WallRenderer() {

}

void WallRenderer::setNeighbours(RoomUtils::NeighbourFlags neighbours) {
    _neighbours = neighbours;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF WallRenderer::size(const QSize& cellSize) const {
    return cellSize;
}

void WallRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const qreal sectionWidth = bounds.width() / 4;
    const qreal sectionHeight = bounds.height() / 4;

    if(isDirty () || _wallPath.isEmpty())
        _wallPath = basePath(bounds, _neighbours);

    QBrush brush(paletteColor (Color_Wall), Qt::SolidPattern);
    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->setPen(Qt::NoPen);
    painter->setBrush(brush);
    painter->drawPath(_wallPath);

    painter->setPen(QPen(paletteColor(Color_Gray), 2));
    painter->drawLine(bounds.left() + sectionWidth, bounds.top() + sectionHeight, bounds.left () + (sectionWidth * 2), bounds.top() + sectionHeight);
    painter->drawLine(bounds.right() - sectionWidth, bounds.bottom() - sectionHeight, bounds.right () - (sectionWidth * 2), bounds.bottom() - sectionHeight);

//    QPainterPathStroker strokerPath(QPen(Qt::white, 1));

//    painter->strokePath (strokerPath.createStroke(_wallPath), QPen(Qt::white));

    setDirty(false);
}

QImage WallRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    WallRenderer renderer;

    renderer.setNeighbours(RoomUtils::NeighbourFlag_NorthEast|RoomUtils::NeighbourFlag_SouthWest);

    return renderer.drawImage(size, fillColor, border);
}

QPainterPath WallRenderer::basePath(const QRectF& rect, RoomUtils::NeighbourFlags neighbours) const {
    PaintUtils::CornerFlags flags = PaintUtils::CornerFlag_None;

    if((neighbours & (RoomUtils::NeighbourFlag_North|RoomUtils::NeighbourFlag_NorthEast|RoomUtils::NeighbourFlag_East)) == 0)
        flags |= PaintUtils::CornerFlag_TopRight;

    if((neighbours & (RoomUtils::NeighbourFlag_South|RoomUtils::NeighbourFlag_SouthEast|RoomUtils::NeighbourFlag_East)) == 0)
        flags |= PaintUtils::CornerFlag_BottomRight;

    if((neighbours & (RoomUtils::NeighbourFlag_South|RoomUtils::NeighbourFlag_SouthWest|RoomUtils::NeighbourFlag_West)) == 0)
        flags |= PaintUtils::CornerFlag_BottomLeft;

    if((neighbours & (RoomUtils::NeighbourFlag_North|RoomUtils::NeighbourFlag_NorthWest|RoomUtils::NeighbourFlag_West)) == 0)
        flags |= PaintUtils::CornerFlag_TopLeft;

    return PaintUtils::roundRectPath(rect, flags);
}
