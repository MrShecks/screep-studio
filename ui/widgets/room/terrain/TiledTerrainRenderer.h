/*
 * File: TiledTerrainRenderer.h
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

#ifndef _TILEDTERRAINRENDERER_H
#define _TILEDTERRAINRENDERER_H

#include "TerrainRenderer.h"
#include "ui/widgets/room/utils/TerrainTileset.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _DEBUG_TILED_RENDERER   0
#define _DEBUG_TILE_FLAGS       _DEBUG_TILED_RENDERER && 1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TiledTerrainRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TiledTerrainRenderer : public TerrainRenderer {
    typedef TerrainRenderer _super;

    const static QColor DEF_COLOR_TERRAIN_PLAIN;
    const static QColor DEF_COLOR_TERRAIN_WALL;
    const static QColor DEF_COLOR_TERRAIN_SWAMP;

public:
    TiledTerrainRenderer(const QGraphicsScene* scene, int cellWidth, int cellHeight);
    virtual ~TiledTerrainRenderer();

    void beginRender(QPainter* painter, const QRectF& rect);
    void endRender(QPainter* painter, const QRectF& rect);

    void drawCell(QPainter* painter, const QRectF& cellRect, Screeps::TerrainFlags terrainFlags, RoomUtils::NeighbourFlags flags);

private:
    TerrainTileset _plainTileset;
    TerrainTileset _wallTileset;
};

#endif // _TILEDTERRAINRENDERER_H
