/*
 * File: RoomGraphicsScene.h
 * Created: 2018-11-24
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

#ifndef _ROOMGRAPHICSSCENE_H
#define _ROOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPainter>
#include <QPixmap>
#include <QMap>

#include "../../models/room/RoomModel.h"
#include "./entities/RoomGraphicsItem.h"
#include "./terrain/ClassicTerrainRenderer.h"
#include "./terrain/TiledTerrainRenderer.h"
#include "./utils/TerrainTileset.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _DEBUG_ROOM_SCENE           1
#define _DEBUG_ENTITY_MAP           _DEBUG_ROOM_SCENE && 0
#define _DEBUG_SCENE_UPDATES        _DEBUG_ROOM_SCENE && 0
#define _DEBUG_ENABLE_ROOM_TILES    _DEBUG_ROOM_SCENE && 0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsView;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsScene
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsScene : public QGraphicsScene {
    typedef QGraphicsScene _super;

    friend class RoomGraphicsItem;

    Q_OBJECT

    const static QColor DEF_COLOR_GRID;

public:
    const static int CELL_WIDTH         = 64;
    const static int CELL_HEIGHT        = CELL_WIDTH;

    RoomGraphicsScene(QObject* parent = nullptr);
    virtual ~RoomGraphicsScene();

    void setModel(RoomModel::TSharedPtr roomModel);

    int sceneWidth() const;
    int sceneHeight() const;

    const RoomTerrainModel& terrain() const;

    void showGrid(bool show);

    //
    // QGraphicsScene
    //

    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) Q_DECL_OVERRIDE;

public slots:
    void setTerrain(const RoomTerrainModel& terrain);

private slots:
    void _onRoomEntityAdded(const QString& id, const RoomEntity& entity);
    void _onRoomEntityUpdated(const QString& id, const RoomEntity& entity, int gameTime);
    void _onRoomEntityRemoved(const QString& id);

private:
    typedef QMap<QString, RoomGraphicsItem *> TEntityMap;

    RoomModel::TSharedPtr _roomModel;
    QString _userId;
    bool _showGrid;

#if _DEBUG_ENABLE_ROOM_TILES
    TiledTerrainRenderer _terrainRenderer;
#else
    ClassicTerrainRenderer _terrainRenderer;
#endif // _DEBUG_ENABLE_ROOM_TILES

    TEntityMap _entities;

    void drawBackground(QPainter* painter, const QRectF& rect) Q_DECL_OVERRIDE;

#if _DEBUG_ENTITY_MAP
    void dbgDumpEntityMap();
#endif // _DEBUG_ENTITY_MAP
};

#endif // _ROOMGRAPHICSSCENE_H
