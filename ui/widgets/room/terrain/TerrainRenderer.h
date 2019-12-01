/*
 * File: TerrainRenderer.h
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

#ifndef _TERRAINRENDERER_H
#define _TERRAINRENDERER_H

#include "models/room/RoomTerrainModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class QGraphicsScene;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TerrainRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TerrainRenderer {

public:
    TerrainRenderer(const QGraphicsScene* scene, int cellWidth, int cellHeight);
    virtual ~TerrainRenderer();

    virtual void beginRender(QPainter* painter, const QRectF& rect);
    virtual void endRender(QPainter* painter, const QRectF& rect);

    virtual void drawCell(QPainter* painter, const QRectF& cellRect, Screeps::TerrainFlags terrainFlags, RoomUtils::NeighbourFlags flags) = 0;

protected:
    const QGraphicsScene* scene() const         { return _scene; }

    int cellWidth() const                       { return _cellWidth; }
    int cellHeight() const                      { return _cellHeight; }

private:
    const QGraphicsScene* _scene;

    int _cellWidth;
    int _cellHeight;
};

#endif // _TERRAINRENDERER_H
