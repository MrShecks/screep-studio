/*
 * File: RoomGraphicsItemSpawn.h
 * Created: 2018-12-11
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

#ifndef _ROOMGRAPHICSITEMSPAWN_H
#define _ROOMGRAPHICSITEMSPAWN_H

#include <QPropertyAnimation>

#include "RoomGraphicsItem.h"
#include "../renderers/SpawnRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SpawnEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SpawnEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:
    enum State {
        State_Idle,
        State_Spawning
    };

    SpawnEntity(const RoomEntity& entity)
        : _super(entity) {
    }

    State state() const                 { return hasObject("spawning") ? State_Spawning : State_Idle; }

    int energy() const                  { return getStoredResourceAmount("energy"); }
    int energyCapacity() const          { return getStoredResourceCapacity("energy"); }

    int elapsedSpawnTime() const;
    int totalSpawnTime() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemSpawn
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemSpawn : public TRoomGraphicsItem<SpawnEntity> {
    typedef TRoomGraphicsItem<SpawnEntity> _super;

    static const int SPAWN_ANIMATION_DURATION   = 3000;

public:
    RoomGraphicsItemSpawn(const SpawnEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemSpawn();

private:
    SpawnRenderer _spawnRenderer;
    QPropertyAnimation _spawnAnimation;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const SpawnEntity& current, const SpawnEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMSPAWN_H
