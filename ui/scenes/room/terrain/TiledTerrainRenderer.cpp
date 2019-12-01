/*
 * File: TiledTerrainRenderer.cpp
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

#include <QPainter>

#include "TiledTerrainRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor TiledTerrainRenderer::DEF_COLOR_TERRAIN_PLAIN  = QColor("#2b2b2b");
const QColor TiledTerrainRenderer::DEF_COLOR_TERRAIN_WALL   = QColor("#181818");
const QColor TiledTerrainRenderer::DEF_COLOR_TERRAIN_SWAMP  = QColor("#292b18");    // "#4a501e"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TiledTerrainRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TiledTerrainRenderer::TiledTerrainRenderer(const QGraphicsScene* scene, int cellWidth, int cellHeight)
    : _super(scene, cellWidth, cellHeight),
      _plainTileset(":/assets/images/plain_tileset.png", cellWidth, cellHeight),
      _wallTileset(":/assets/images/wall_tileset.png", cellWidth, cellHeight) {

    //_plainTileset.addMapping (  7, 44);
    _plainTileset.addMapping ( 28,  4);
    _plainTileset.addMapping ( 31, 27);
    _plainTileset.addMapping (124,  5);
    _plainTileset.addMapping (127, 12);
    _plainTileset.addMapping (255, 13 /*37*/);

    _wallTileset.addMapping (  0,  0);
    _wallTileset.addMapping (  1, 23);
    _wallTileset.addMapping (  4,  1);
    _wallTileset.addMapping (  5, 40);
    _wallTileset.addMapping (  7, 44);
    _wallTileset.addMapping ( 16, 31);
    _wallTileset.addMapping ( 21, 32);
    _wallTileset.addMapping ( 28,  4);
    _wallTileset.addMapping ( 31, 27);
    _wallTileset.addMapping ( 64,  7);
    _wallTileset.addMapping ( 80, 15);
    _wallTileset.addMapping ( 81, 26);
    _wallTileset.addMapping ( 85, 18);
    _wallTileset.addMapping ( 92,  2);
    _wallTileset.addMapping ( 93, 34);
    _wallTileset.addMapping ( 95, 19);
    _wallTileset.addMapping (112,  3);
    _wallTileset.addMapping (119, 35);
    _wallTileset.addMapping (125, 29);
    _wallTileset.addMapping (124,  5);
    _wallTileset.addMapping (127, 12);
    _wallTileset.addMapping (193, 43);
    _wallTileset.addMapping (197, 46);
    _wallTileset.addMapping (199, 45);
    _wallTileset.addMapping (209, 22);
    _wallTileset.addMapping (215, 21);
    _wallTileset.addMapping (221, 11);
    _wallTileset.addMapping (223, 36);
    _wallTileset.addMapping (241, 38);
    _wallTileset.addMapping (245, 14);
    _wallTileset.addMapping (247, 20);
    _wallTileset.addMapping (253, 28);
    _wallTileset.addMapping (255, 13 /*37*/);
}

TiledTerrainRenderer::~TiledTerrainRenderer() {

}

void TiledTerrainRenderer::beginRender(QPainter* painter, const QRectF& rect) {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, false);

    Q_UNUSED(rect);
}

void TiledTerrainRenderer::endRender(QPainter* painter, const QRectF& rect) {
    painter->restore();

    Q_UNUSED(rect);
}

void TiledTerrainRenderer::drawCell(QPainter* painter, const QRectF& cellRect, Screeps::TerrainFlags terrainFlags, RoomUtils::NeighbourFlags flags) {
#if _DEBUG_TILE_FLAGS
    const QString flagText = QString("%1").arg(flags, 0, 16).toUpper();
#endif // _DEBUG_TILE_FLAGS

    switch(terrainFlags) {
        case Screeps::TerrainFlag_Plain: {
            if(!_plainTileset.drawMappedTile(painter, flags, cellRect)) {
                painter->setPen(QPen(Qt::red, 1));
                painter->fillRect(cellRect, DEF_COLOR_TERRAIN_PLAIN);
            }
#if _DEBUG_TILE_FLAGS
                painter->setPen(Qt::yellow);
                painter->drawText (cellRect, Qt::AlignCenter, flagText);
#endif // _DEBUG_TILE_FLAGS
        }
        break;

        case Screeps::TerrainFlag_Wall: {
            if(!_wallTileset.drawMappedTile(painter, flags, cellRect)) {
                painter->setPen(Qt::NoPen);
                painter->fillRect(cellRect, DEF_COLOR_TERRAIN_WALL);
            }

#if _DEBUG_TILE_FLAGS
            painter->setPen(Qt::white);
            painter->drawText (cellRect, Qt::AlignCenter, flagText);
#endif // _DEBUG_TILE_FLAGS
        }
        break;

        case Screeps::TerrainFlag_Swamp: {
            painter->setPen(Qt::NoPen);
            painter->fillRect(cellRect, DEF_COLOR_TERRAIN_SWAMP);

#if _DEBUG_TILE_FLAGS
            painter->setPen(Qt::red);
            painter->drawText (cellRect, Qt::AlignCenter, flagText);
#endif // _DEBUG_TILE_FLAGS
        }
        break;

        default: {

        }
        break;
    }
}
