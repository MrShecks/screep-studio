/*
 * File: ClassicTerrainRenderer.h
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

#ifndef _CLASSICTERRAINRENDERER_H
#define _CLASSICTERRAINRENDERER_H

#include <QColor>
#include <QPainter>
#include <QPixmap>

#include "TerrainRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _DBG_CLASSIC_TERRAIN_RENDERER       0
#define _DBG_TERRAIN_FLAGS                  _DBG_CLASSIC_TERRAIN_RENDERER && 1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ClassicTerrainRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ClassicTerrainRenderer : public TerrainRenderer {
    typedef TerrainRenderer _super;

    const static QColor DEF_COLOR_BACKGROUND;
    const static QColor DEF_COLOR_TERRAIN_WALL;
    const static QColor DEF_COLOR_TERRAIN_SWAMP;

public:
    ClassicTerrainRenderer(const QGraphicsScene* scene, int cellWidth, int cellHeight);
    virtual ~ClassicTerrainRenderer();

    void beginRender(QPainter* painter, const QRectF& rect);
    void endRender(QPainter* painter, const QRectF& rect);

    void drawCell(QPainter* painter, const QRectF& cellRect, Screeps::TerrainFlags terrainFlags, RoomUtils::NeighbourFlags flags);

private:
    QPixmap _background;
    QPixmap _backgroundMask;

    void drawTiledBackground(QPainter* painter, const QPixmap& tile, qreal opacity = 1.0, QPainter::CompositionMode compositionMode = QPainter::CompositionMode_SourceOver);
    QPainterPath rectanglePath(const QRectF& rect, RoomUtils::NeighbourFlags neighbours) const;
};

#endif // _CLASSICTERRAINRENDERER_H
