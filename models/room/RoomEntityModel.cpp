/*
 * File: RoomEntityModel.cpp
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

#include "RoomEntityModel.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif // QT_DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomEntityModel
// Model used to track the dynamic room entities as well as manage the constructed
// infrastructure (roads, walls, ramparts etc)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomEntityModel::RoomEntityModel()
    : _isLoading(false) {

}

RoomEntityModel::~RoomEntityModel() {
#if _DBG_ROOMENTITYMODEL
    for(int type = 0; type < MapType_Count; ++type) {
        TRoomCellMap::const_iterator it = _cellMap[type].constBegin();
        TRoomCellMap::const_iterator limit = _cellMap[type].constEnd();

        for(; it != limit; ++it) {
            qDebug() << "Type=" << type << ", Index=" << it.key() << ", Id=" << it.value() << ", Pos=" << RoomUtils::getCellPosition(it.key());
        }
    }
#endif // _DBG_ROOMENTITYMODEL
}

void RoomEntityModel::beginRecover() {
    _isLoading = true;

    for(TRoomCellMap cellMap : _cellMap)
        cellMap.clear();

    _entities.clear();
}

void RoomEntityModel::endRecover() {
    TRoomEntityMap::iterator it = _entities.begin();
    TRoomEntityMap::iterator limit = _entities.end();

    for(; it != limit; ++it) {
        applyMetadata(it.value());
        emit roomEntityAdded(it.key(), it.value());
    }

    _isLoading = false;
}

void RoomEntityModel::addEntity(const QString& id, const QJsonObject& json) {
    Q_ASSERT_X(_entities.find(id) == _entities.end(), "RoomEntityModel::addEntity", "Entity map already contains ID!");
    TRoomEntityMap::iterator it = _entities.insert(id, RoomEntity(json));

    if(it != _entities.end()) {
        QJsonObject data;

        addToCellMap(it.value().entityType(), it.value().pos(), id);

        if(!_isLoading) {
            // TODO: If this is an infrastructure entity we need to update the metadata
            // for it neighbours and emit a update for them

            applyMetadata(it.value());
            emit roomEntityAdded(id, it.value());
        }
    }
}

void RoomEntityModel::updateEntity(const QString& id, const QJsonObject& json, int gameTime) {
    TRoomEntityMap::iterator it;

    if((it = _entities.find(id)) != _entities.end()) {
        it.value().applyUpdate(json);

        if(!_isLoading) {
            applyMetadata(it.value());
            emit roomEntityUpdated(id, it.value(), gameTime);
        }
    }
}

bool RoomEntityModel::removeEntity(const QString& id) {
    TRoomEntityMap::iterator it;

    if((it = _entities.find(id)) != _entities.end()) {
        removeFromCellMap(it.value().entityType(), it.value().pos());
        _entities.erase(it);

        // TODO: If this is an infrastructure entity we need to update the metadata
        // for it neighbours and emit a update for them

        emit roomEntityRemoved(id);
    }

    Q_ASSERT_X(it != _entities.end(), "RoomEntityModel::removeEntity", "Attempt to remove unknown entity!");

    return it != _entities.end();
}

bool RoomEntityModel::exists(const QString& id) const {
    return _entities.find(id) != _entities.end();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomEntityModel::addToCellMap(Screeps::EntityType type, const QPoint& pos, const QString& id) {
    int index;

    if((index = RoomUtils::getCellIndex(pos)) != -1) {
        if(type == Screeps::EntityType_Road)
            _cellMap[MapType_Road].insert(index, id);
        else if(type == Screeps::EntityType_Wall)
            _cellMap[MapType_Wall].insert(index, id);
        else if(type == Screeps::EntityType_Rampart)
            _cellMap[MapType_Rampart].insert(index, id);
    }
}

void RoomEntityModel::removeFromCellMap(Screeps::EntityType type, const QPoint& pos) {
    int index;

    if((index = RoomUtils::getCellIndex(pos)) != -1) {
        if(type == Screeps::EntityType_Road)
            _cellMap[MapType_Road].remove(index);
        else if(type == Screeps::EntityType_Wall)
            _cellMap[MapType_Wall].remove(index);
        else if(type == Screeps::EntityType_Rampart)
            _cellMap[MapType_Rampart].remove(index);
    }
}

void RoomEntityModel::applyMetadata(RoomEntity& entity) {
    QJsonObject data = getMetadata(entity);

    if(!data.isEmpty())
        entity.setMetaData(data);
}

QJsonObject RoomEntityModel::getMetadata(const RoomEntity& entity) {
    QJsonObject data;

    switch(entity.entityType()) {
        case Screeps::EntityType_Wall:      data = getWallEntityMetaData(entity);       break;
        case Screeps::EntityType_Road:      data = getRoadEntityMetaData(entity);       break;
        case Screeps::EntityType_Rampart:   data = getRampartEntityMetaData(entity);    break;

        default: {

        }
        break;
    }

    return data;
}

QJsonObject RoomEntityModel::getWallEntityMetaData(const RoomEntity& entity) const {
    RoomUtils::NeighbourFlags flags = getNeighbours(entity.pos (), _cellMap[MapType_Wall], Screeps::EntityType_Wall);
    QJsonObject data;

    data.insert("neighbours", static_cast<quint16> (flags));

#ifdef QT_DEBUG
    data.insert("dbg_neighbours", getNeighbourNames_dbg(flags));
#endif // QT_DEBUG

    return data;
}

QJsonObject RoomEntityModel::getRoadEntityMetaData(const RoomEntity& entity) const {
    RoomUtils::NeighbourFlags flags = getNeighbours(entity.pos (), _cellMap[MapType_Road], Screeps::EntityType_Road);
    QJsonObject data;

    data.insert("neighbours", static_cast<quint16> (flags));

#ifdef QT_DEBUG
    data.insert("dbg_neighbours", getNeighbourNames_dbg(flags));
#endif // QT_DEBUG

    return data;
}

QJsonObject RoomEntityModel::getRampartEntityMetaData(const RoomEntity& entity) const {

    //
    // FIXME: It's possible to have a non-owned rampart as a neighbour to an
    // owned rampart, in this case we want to ignore that neighbour so will need
    // to compare the current player id to the rampart owner id
    //

    RoomUtils::NeighbourFlags flags = getNeighbours(entity.pos (), _cellMap[MapType_Rampart], Screeps::EntityType_Rampart);
    QJsonObject data;

    data.insert("neighbours", static_cast<quint16> (flags));

#ifdef QT_DEBUG
    data.insert("dbg_neighbours", getNeighbourNames_dbg(flags));
#endif // QT_DEBUG

    return data;
}

RoomUtils::NeighbourFlags RoomEntityModel::getNeighbours(const QPoint& cellPos, const TRoomCellMap& cellMap, Screeps::EntityType entityType) const {
    RoomUtils::NeighbourFlags flags = RoomUtils::NeighbourFlag_None;

    for(int n = 0; n < RoomUtils::Neighbour_Count; ++n) {
        const QPoint pos = RoomUtils::getNeighbourPosition(static_cast<RoomUtils::Neighbours>(n), cellPos);
        const QString entityId = cellMap.value(RoomUtils::getCellIndex(pos), QString("Arse"));
        const TRoomEntityMap::const_iterator it = _entities.constFind(entityId);

        if(it != _entities.constEnd() && it.value().entityType() == entityType)
            flags |= static_cast<RoomUtils::NeighbourFlag>(1 << n);
    }

    return flags;
}

#ifdef QT_DEBUG
QJsonArray RoomEntityModel::getNeighbourNames_dbg(RoomUtils::NeighbourFlags flags) const {
    QJsonArray neighbours;

    static const QString NEIGHBOUR_NAMES[] = {
        QStringLiteral("North"),
        QStringLiteral("North East"),
        QStringLiteral("East"),
        QStringLiteral("South East"),
        QStringLiteral("South"),
        QStringLiteral("South West"),
        QStringLiteral("West"),
        QStringLiteral("North West")
    };

    for(int n = 0; n < RoomUtils::Neighbour_Count; ++n) {
        if((flags & (1 << n)) != 0)
            neighbours.append(NEIGHBOUR_NAMES[n]);
    }

    return neighbours;
}
#endif // QT_DEBUG
