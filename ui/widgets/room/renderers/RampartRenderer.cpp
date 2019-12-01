/*
 * File: RampartRenderer.cpp
 * Created: 2019-1-24
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

#include "RampartRenderer.h"
#include "utils/PaintUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RampartRenderer
// Utility class to draw the "Rampart" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RampartRenderer::RampartRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _opacity(ENTITY_OPACITY),
      _neighbours(RoomUtils::NeighbourFlag_None) {

    _neighbours |= RoomUtils::NeighbourFlag_North;
}

RampartRenderer::~RampartRenderer() {

}

void RampartRenderer::setOpacity(qreal opacity) {
    _opacity = opacity;
    setDirty(true);
}

void RampartRenderer::setNeighbours(RoomUtils::NeighbourFlags neighbours) {
    _neighbours = neighbours;
    setDirty(true);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RampartRenderer::size(const QSize& cellSize) const {
    return cellSize;
}

void RampartRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const QColor fillColor = paletteColor(isPlayerOwned () ? Color_Player_Rampart : Color_Enemy_Rampart);
    const QColor penColor = paletteColor(isPlayerOwned () ? Color_Player_Rampart_Border : Color_Enemy_Rampart_Border);
    const qreal penWidth = scaledWidth(bounds.size(), BORDER_PEN_SCALE);

    if(isDirty()) {
        if(_rampartPath.isEmpty())
            _rampartPath = basePath(bounds, _neighbours);

        if(_edgePath.isEmpty() && _neighbours != RoomUtils::NeighbourFlag_All)
            _edgePath = edgePath(bounds.adjusted(penWidth / 2, penWidth / 2, -(penWidth / 2), -(penWidth / 2)), _neighbours, penWidth);
    }

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setOpacity(_opacity);
    painter->setPen(Qt::NoPen);
    painter->setBrush(fillColor);
    painter->drawPath(_rampartPath);

    if(!_edgePath.isEmpty ()) {
        painter->strokePath(_edgePath, QPen(penColor, penWidth/*, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin*/));
    }

    setDirty(false);
}

QImage RampartRenderer::toImage(const QSize& size, QColor fillColor /* = Qt::white */, const QSize& border /* = QSize() */) {
    RampartRenderer renderer;

    renderer.setOpacity(0.5);
    renderer.setOwner(RampartRenderer::OwnerType_Player);
    renderer.setNeighbours(RoomUtils::NeighbourFlag_NorthWest|RoomUtils::NeighbourFlag_SouthEast);

    return renderer.drawImage(size, fillColor, border);
}

QPainterPath RampartRenderer::basePath(const QRectF& rect, RoomUtils::NeighbourFlags neighbours) const {
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

QPainterPath RampartRenderer::edgePath(const QRectF &rect, RoomUtils::NeighbourFlags neighbours, qreal penWidth) const {
    QPainterPath path;

    //
    // FIXME: Is there a better way to do this?
    //

    if(neighbours != RoomUtils::NeighbourFlag_All) {
        if(neighbours == RoomUtils::NeighbourFlag_None)
            path.addEllipse(rect);
        else {
#if 1
            const qreal halfWidth = rect.width() / 2;
            const qreal halfHeight = rect.height() / 2;

            if((neighbours & (RoomUtils::NeighbourFlag_North|RoomUtils::NeighbourFlag_NorthEast|RoomUtils::NeighbourFlag_East)) == 0) {
                path.moveTo(rect.left() + halfWidth, rect.top());
                path.arcTo(rect, 90, -90);
            } else {
                if((neighbours & RoomUtils::NeighbourFlag_North) == 0) {
                    path.moveTo(rect.left() + halfWidth + penWidth, rect.top());
                    path.lineTo(rect.topRight());
                }

                if((neighbours & RoomUtils::NeighbourFlag_East) == 0) {
                    path.moveTo(rect.topRight());
                    path.lineTo(rect.right(), rect.top() + halfHeight - penWidth);
                }
            }

            if((neighbours & (RoomUtils::NeighbourFlag_South|RoomUtils::NeighbourFlag_SouthEast|RoomUtils::NeighbourFlag_East)) == 0) {
                path.moveTo(rect.right(), rect.top() + halfHeight);
                path.arcTo(rect, 0, -90);
            } else {
                if((neighbours & RoomUtils::NeighbourFlag_East) == 0) {
                    path.moveTo(rect.right(), rect.top() + halfHeight);
                    path.lineTo(rect.bottomRight());
                }

                if((neighbours & RoomUtils::NeighbourFlag_South) == 0) {
                    path.moveTo(rect.bottomRight());
                    path.lineTo(rect.right() - halfWidth + penWidth, rect.bottom());
                }
            }

            if((neighbours & (RoomUtils::NeighbourFlag_South|RoomUtils::NeighbourFlag_SouthWest|RoomUtils::NeighbourFlag_West)) == 0) {
                path.moveTo(rect.right() - halfWidth, rect.bottom());
                path.arcTo(rect, -90, -90);
            } else {
                if((neighbours & RoomUtils::NeighbourFlag_South) == 0) {
                    path.moveTo(rect.right() - halfWidth, rect.bottom());
                    path.lineTo(rect.bottomLeft());
                }

                if((neighbours & RoomUtils::NeighbourFlag_West) == 0) {
                    path.moveTo(rect.bottomLeft());
                    path.lineTo(rect.left(), rect.bottom() - halfHeight + penWidth);
                }
            }

            if((neighbours & (RoomUtils::NeighbourFlag_North|RoomUtils::NeighbourFlag_NorthWest|RoomUtils::NeighbourFlag_West)) == 0) {
                path.moveTo(rect.left(), rect.bottom() - halfHeight);
                path.arcTo(rect, -180, -90);
            } else {
                if((neighbours & RoomUtils::NeighbourFlag_West) == 0) {
                    path.moveTo(rect.left(), rect.bottom() - halfHeight);
                    path.lineTo(rect.topLeft());
                }

                if((neighbours & RoomUtils::NeighbourFlag_North) == 0) {
                    path.moveTo(rect.topLeft());
                    path.lineTo(rect.left() + halfWidth, rect.top());
                }
            }
#else
            const qreal halfWidth = rect.width() / 2;
            const qreal halfHeight = rect.height() / 2;

            if((neighbours & (RoomUtils::NeighbourFlag_North|RoomUtils::NeighbourFlag_NorthEast|RoomUtils::NeighbourFlag_East)) == 0) {
                path.moveTo(rect.left() + halfWidth, rect.top());
                path.arcTo(rect, 90, -90);
            } else {
                if((neighbours & RoomUtils::NeighbourFlag_North) == 0) {
                    path.moveTo(rect.left() + halfWidth, rect.top());
                    path.lineTo(rect.topRight());
                }

                if((neighbours & RoomUtils::NeighbourFlag_East) == 0) {
                    path.moveTo(rect.topRight());
                    path.lineTo(rect.right(), rect.top() + halfHeight);
                }
            }

            if((neighbours & (RoomUtils::NeighbourFlag_South|RoomUtils::NeighbourFlag_SouthEast|RoomUtils::NeighbourFlag_East)) == 0) {
                path.moveTo(rect.right(), rect.top() + halfHeight);
                path.arcTo(rect, 0, -90);
            } else {
                if((neighbours & RoomUtils::NeighbourFlag_East) == 0) {
                    path.moveTo(rect.right(), rect.top() + halfHeight);
                    path.lineTo(rect.bottomRight());
                }

                if((neighbours & RoomUtils::NeighbourFlag_South) == 0) {
                    path.moveTo(rect.bottomRight());
                    path.lineTo(rect.right() - halfWidth, rect.bottom());
                }
            }

            if((neighbours & (RoomUtils::NeighbourFlag_South|RoomUtils::NeighbourFlag_SouthWest|RoomUtils::NeighbourFlag_West)) == 0) {
                path.moveTo(rect.right() - halfWidth, rect.bottom());
                path.arcTo(rect, -90, -90);
            } else {
                if((neighbours & RoomUtils::NeighbourFlag_South) == 0) {
                    path.moveTo(rect.right() - halfWidth, rect.bottom());
                    path.lineTo(rect.bottomLeft());
                }

                if((neighbours & RoomUtils::NeighbourFlag_West) == 0) {
                    path.moveTo(rect.bottomLeft());
                    path.lineTo(rect.left(), rect.bottom() - halfHeight);
                }
            }

            if((neighbours & (RoomUtils::NeighbourFlag_North|RoomUtils::NeighbourFlag_NorthWest|RoomUtils::NeighbourFlag_West)) == 0) {
                path.moveTo(rect.left(), rect.bottom() - halfHeight);
                path.arcTo(rect, -180, -90);
            } else {
                if((neighbours & RoomUtils::NeighbourFlag_West) == 0) {
                    path.moveTo(rect.left(), rect.bottom() - halfHeight);
                    path.lineTo(rect.topLeft());
                }

                if((neighbours & RoomUtils::NeighbourFlag_North) == 0) {
                    path.moveTo(rect.topLeft());
                    path.lineTo(rect.left() + halfWidth, rect.top());
                }
            }
#endif
        }
    }

    return path;
}
