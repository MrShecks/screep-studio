/*
 * File: RoomGraphicsScene.cpp
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

#include <QGraphicsSceneMouseEvent>
#include <QtMath>

#include "RoomGraphicsScene.h"
#include "RoomGraphicsView.h"

#include <QtDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor RoomGraphicsScene::DEF_COLOR_GRID              = QColor("#444444");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsScene
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsScene::RoomGraphicsScene(QObject* parent /* = nullptr */)
    : _super(0, 0, RoomModel::ROOM_WIDTH * CELL_WIDTH, RoomModel::ROOM_HEIGHT * CELL_HEIGHT, parent),
      _roomModel(0),
      _showGrid(false),
      _terrainRenderer(this, CELL_WIDTH, CELL_HEIGHT) {

}

RoomGraphicsScene::~RoomGraphicsScene() {

}

void RoomGraphicsScene::setModel(RoomModel::TSharedPtr roomModel) {
    if (_roomModel != roomModel) {

        if(_roomModel) {
            disconnect(_roomModel.data(), &RoomModel::roomEntityAdded, this, &RoomGraphicsScene::_onRoomEntityAdded);
            disconnect(_roomModel.data(), &RoomModel::roomEntityUpdated, this, &RoomGraphicsScene::_onRoomEntityUpdated);
            disconnect(_roomModel.data(), &RoomModel::roomEntityRemoved, this, &RoomGraphicsScene::_onRoomEntityRemoved);

            disconnect(&_roomModel->terrainModel(), &RoomTerrainModel::terrainUpdated, this, &RoomGraphicsScene::setTerrain);
        }

        if(roomModel) {
            connect(roomModel.data(), &RoomModel::roomEntityAdded, this, &RoomGraphicsScene::_onRoomEntityAdded);
            connect(roomModel.data(), &RoomModel::roomEntityUpdated, this, &RoomGraphicsScene::_onRoomEntityUpdated);
            connect(roomModel.data(), &RoomModel::roomEntityRemoved, this, &RoomGraphicsScene::_onRoomEntityRemoved);

            connect(&roomModel->terrainModel(), &RoomTerrainModel::terrainUpdated, this, &RoomGraphicsScene::setTerrain);
        }

        _roomModel = roomModel;
    }
}

int RoomGraphicsScene::sceneWidth() const {
    return _roomModel->terrainModel ().width () * CELL_WIDTH;
}

int RoomGraphicsScene::sceneHeight() const {
    return _roomModel->terrainModel().height() * CELL_HEIGHT;
}

const RoomTerrainModel& RoomGraphicsScene::terrain() const {
    return _roomModel->terrainModel();
}

void RoomGraphicsScene::showGrid(bool showGrid) {
    _showGrid = showGrid;
    invalidate(sceneRect (), QGraphicsScene::BackgroundLayer);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {

    if(mouseEvent->type() == QGraphicsSceneMouseEvent::GraphicsSceneMousePress) {
        QGraphicsItem* item;

        qDebug() << "mouseEvent=" << mouseEvent->type ()
                 << "pos=" << mouseEvent->pos()
                 << ", screenPos=" << mouseEvent->screenPos()
                 << ", scenePos=" << mouseEvent->scenePos();

        if((item = itemAt(mouseEvent->scenePos(), QTransform())) != 0) {

        }
    }

    _super::mousePressEvent(mouseEvent);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomGraphicsScene::setTerrain(const RoomTerrainModel& terrain) {
    const qreal width = terrain.width () * CELL_WIDTH;
    const qreal height = terrain.height() * CELL_HEIGHT;

    setSceneRect(0, 0, width, height);
    invalidate(0, 0, width, height, QGraphicsScene::BackgroundLayer);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomGraphicsScene::_onRoomEntityAdded(const QString& id, const RoomEntity& entity) {
#if _DEBUG_SCENE_UPDATES
    qDebug() << "Id=" << id << ", Type=" << entity.type();
#endif // _DEBUG_SCENE_UPDATES

    RoomGraphicsItem* item = RoomGraphicsItem::create(entity.type(), entity, QSize(CELL_WIDTH, CELL_HEIGHT));

    addItem(item);
    _entities.insert(id, item);

#if _DEBUG_ENTITY_MAP
    dbgDumpEntityMap();
#endif // _DEBUG_ENTITY_MAP

}

void RoomGraphicsScene::_onRoomEntityUpdated(const QString& id, const RoomEntity& entity, int gameTime) {
#if _DEBUG_SCENE_UPDATES
    qDebug() << "Id=" << id << ", Type=" << entity.type() << ", GameTime=" << gameTime;
#endif // _DEBUG_SCENE_UPDATES

    TEntityMap::iterator it;

    if((it = _entities.find(id)) != _entities.end()) {
        Q_ASSERT(it.value() != nullptr);

        it.value()->applyUpdate(entity, gameTime);
    }
}

void RoomGraphicsScene::_onRoomEntityRemoved(const QString& id) {
#if _DEBUG_SCENE_UPDATES
    qDebug() << "Id=" << id;
#endif // _DEBUG_SCENE_UPDATES

    TEntityMap::iterator it;

    if((it = _entities.find(id)) != _entities.end()) {
        RoomGraphicsItem* item = it.value();
        Q_ASSERT(item != nullptr);

#if _DEBUG_SCENE_UPDATES
        qDebug() << "Id=" << id << ", Type=" << item->type() << " *** REMOVED";
#endif // _DEBUG_SCENE_UPDATES

        removeItem(item);
        _entities.erase(it);

        // Once we remove an item from QGraphicsScene we take back
        // ownership so it is our responsibility to free the object.

        delete item;
    }

#if _DEBUG_ENTITY_MAP
    dbgDumpEntityMap();
#endif // _DEBUG_ENTITY_MAP

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomGraphicsScene::drawBackground(QPainter* painter, const QRectF& rect) {

    if(_roomModel && !_roomModel->terrainModel().isEmpty()) {
        const RoomTerrainModel& terrain = _roomModel->terrainModel();

        painter->save();
        _terrainRenderer.beginRender(painter, rect);

        for(int y = 0; y < terrain.height(); ++y) {
            for(int x = 0; x < terrain.width(); ++x) {
                const QRectF cellRect = QRectF(x * CELL_WIDTH, y * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT);

                if(rect.intersects (cellRect)) {
                    const Screeps::TerrainFlags terrainTypeFlags = terrain.getTerrainType (x, y);
                    const RoomUtils::NeighbourFlags flags = terrain.getNeighbourFlags(x, y);

                    _terrainRenderer.drawCell(painter, cellRect, terrainTypeFlags, flags);

                    if(_showGrid) {
                        painter->setPen(DEF_COLOR_GRID);
                        painter->drawRect(cellRect);
                    }
                }
            }
        }

        _terrainRenderer.endRender(painter, rect);
        painter->restore();
    }
}

#if _DEBUG_ENTITY_MAP
void RoomGraphicsScene::dbgDumpEntityMap() {
    TEntityMap::const_iterator it = _entities.constBegin();
    TEntityMap::const_iterator limit = _entities.constEnd();

    qDebug() << "Room Scene Entity Map";
    qDebug() << "-----------------------------------------------------------------";

    for(; it != limit; ++it) {
        RoomGraphicsItem* item = static_cast<RoomGraphicsItem *>(it.value());

        qDebug() << "Entity: Id=" << it.key () << ", Type=" << item->type();
    }

    qDebug() << "-----------------------------------------------------------------" << "\n";

}
#endif // _DEBUG_ENTITY_MAP
