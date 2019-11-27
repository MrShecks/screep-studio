/*
 * File: ClassicTerrainRenderer.cpp
 * Created: 2018-12-24
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

#include <QGraphicsScene>
#include <QPainter>
#include <QRectF>

#include "ClassicTerrainRenderer.h"
#include "utils/PaintUtils.h"

#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor ClassicTerrainRenderer::DEF_COLOR_BACKGROUND        = QColor("#202020");   // "#353535"
const QColor ClassicTerrainRenderer::DEF_COLOR_TERRAIN_WALL      = QColor("#181818");
const QColor ClassicTerrainRenderer::DEF_COLOR_TERRAIN_SWAMP     = QColor("#292b18");   // "#4a501e"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ClassicTerrainRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ClassicTerrainRenderer::ClassicTerrainRenderer(const QGraphicsScene* scene, int cellWidth, int cellHeight)
    : _super(scene, cellWidth, cellHeight),
      _background(":/assets/images/ground.png"),
      _backgroundMask(":/assets/images/ground_mask.png") {
}

ClassicTerrainRenderer::~ClassicTerrainRenderer() {

}

void ClassicTerrainRenderer::beginRender(QPainter* painter, const QRectF& rect) {

    painter->setRenderHint(QPainter::Antialiasing, false);
    painter->fillRect(rect, DEF_COLOR_BACKGROUND);

    drawTiledBackground(painter, _background, 0.4);
}

void ClassicTerrainRenderer::endRender(QPainter* painter, const QRectF& rect) {
    drawTiledBackground(painter, _backgroundMask, 0.15, QPainter::CompositionMode_Multiply);

    Q_UNUSED(rect);
}

void ClassicTerrainRenderer::drawCell(QPainter* painter, const QRectF& cellRect, Screeps::TerrainFlags terrainFlags, RoomUtils::NeighbourFlags flags) {
    switch(terrainFlags) {
        case Screeps::TerrainFlag_Plain: {

        }
        break;

        case Screeps::TerrainFlag_Wall:
        case Screeps::TerrainFlag_SwampyWall: {
            const QPainterPath path = rectanglePath(cellRect, flags);

            painter->setPen(Qt::NoPen);

            if(terrainFlags & Screeps::TerrainFlag_Swamp) {
                painter->fillRect(cellRect, DEF_COLOR_TERRAIN_SWAMP);
            }

            painter->fillPath(path, DEF_COLOR_TERRAIN_WALL);

        }
        break;

        case Screeps::TerrainFlag_Swamp: {
            const QPainterPath path = rectanglePath(cellRect, flags);

            painter->setPen(Qt::NoPen);
            painter->fillPath(path, DEF_COLOR_TERRAIN_SWAMP);
        }
        break;

        default: {

        }
        break;
    }

#if _DBG_TERRAIN_FLAGS
    QString flagText = QString("%1").arg(terrainFlags, 0, 16).toUpper();

    painter->setPen(Qt::white);
    painter->drawText(cellRect, Qt::AlignCenter, flagText);
#endif // _DBG_TERRAIN_FLAGS

    Q_UNUSED(flags);
}

void ClassicTerrainRenderer::drawTiledBackground(QPainter* painter, const QPixmap& tile, qreal opacity /* = 1.0 */, QPainter::CompositionMode compositionMode /* = QPainter::CompositionMode_SourceOver */) {
    const int sceneWidth = scene()->width();
    const int sceneHeight = scene()->height();
    const int rowCount = qCeil(static_cast<qreal>(sceneHeight) / tile.height());
    const int columnCount = qCeil(static_cast<qreal>(sceneWidth) / tile.width());

    const qreal oldOpacity = painter->opacity();
    const QPainter::CompositionMode oldCompositionMode = painter->compositionMode();

    painter->setOpacity(opacity);
    painter->setCompositionMode(compositionMode);

    for(int column = 0; column < columnCount; ++column) {
        int tileWidth = qMin(sceneWidth - (column * tile.width ()), tile.width());

        for(int row = 0; row < rowCount; ++row) {
            int tileHeight = qMin(sceneHeight - (row * tile.height ()), tile.height());

            painter->drawPixmap (column * tile.width(), row * tile.height(), tile, 0, 0, tileWidth, tileHeight);
        }
    }

    painter->setOpacity(oldOpacity);
    painter->setCompositionMode(oldCompositionMode);
}

QPainterPath ClassicTerrainRenderer::rectanglePath(const QRectF& rect, RoomUtils::NeighbourFlags neighbours) const {
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


