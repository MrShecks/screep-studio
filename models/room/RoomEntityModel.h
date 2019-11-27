/*
 * File: RoomEntityModel.h
 * Created: 2019-1-3
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

#ifndef ROOMENTITYMODEL_H
#define ROOMENTITYMODEL_H

#include <QJsonObject>
#include <QObject>
#include <QHash>
#include <QPoint>

#ifdef QT_DEBUG
#include <QJsonArray>
#endif // QT_DEBUG

#include "ScreepsApi.h"
#include "RoomUtils.h"
#include "RoomEntity.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _DBG_ROOMENTITYMODEL    0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomEntityModel
// Model used to track the dynamic room entities as well as manage the constructed
// infrastructure (roads, walls, ramparts etc)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomEntityModel : public QObject {
    typedef QObject _super;

    Q_OBJECT

public:
    RoomEntityModel();
    virtual ~RoomEntityModel();

    void beginRecover();
    void endRecover();

    void addEntity(const QString& id, const QJsonObject& json);
    void updateEntity(const QString& id, const QJsonObject& json, int gameTime);

    bool removeEntity(const QString& id);
    bool exists(const QString& id) const;

signals:
    void roomEntityAdded(const QString& id, const RoomEntity& entity);
    void roomEntityUpdated(const QString& id, const RoomEntity& entity, int gameTime);
    void roomEntityRemoved(const QString& id);

private:
    enum MapType {
        MapType_Road,
        MapType_Wall,
        MapType_Rampart,

        MapType_Count
    };

    typedef QHash<QString, RoomEntity> TRoomEntityMap;
    typedef QHash<int, QString> TRoomCellMap;

    TRoomEntityMap _entities;
    TRoomCellMap _cellMap[MapType_Count];

    bool _isLoading;

    void addToCellMap(Screeps::EntityType type, const QPoint& pos, const QString& id);
    void removeFromCellMap(Screeps::EntityType type, const QPoint& pos);

    void applyMetadata(RoomEntity& entity);
    QJsonObject getMetadata(const RoomEntity& entity);

    QJsonObject getWallEntityMetaData(const RoomEntity& entity) const;
    QJsonObject getRoadEntityMetaData(const RoomEntity& entity) const;
    QJsonObject getRampartEntityMetaData(const RoomEntity& entity) const;

    RoomUtils::NeighbourFlags getNeighbours(const QPoint& cellPos, const TRoomCellMap& cellMap, Screeps::EntityType entityType) const;

#ifdef QT_DEBUG
    QJsonArray getNeighbourNames_dbg(RoomUtils::NeighbourFlags flags) const;
#endif // QT_DEBUG

};

#endif // ROOMENTITYMODEL_H
