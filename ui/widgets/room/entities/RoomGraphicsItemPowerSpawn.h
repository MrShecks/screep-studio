/*
 * File: RoomGraphicsItemPowerSpawn.h
 * Created: 2019-1-31
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

#ifndef _ROOMGRAPHICSITEMPOWERSPAWN_H
#define _ROOMGRAPHICSITEMPOWERSPAWN_H

#include <QPropertyAnimation>

#include "RoomGraphicsItem.h"
#include "ui/widgets/room/renderers/PowerSpawnRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PowerSpawnEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PowerSpawnEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:
    PowerSpawnEntity(const RoomEntity& entity)
        : _super(entity) {
    }

    int energy() const                  { return getStoredResourceAmount("energy"); }
    int energyCapacity() const          { return getStoredResourceCapacity("energy"); }

    int power() const                   { return getStoredResourceAmount("power"); }
    int powerCapacity() const           { return getStoredResourceCapacity("power"); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemPowerSpawn
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemPowerSpawn : public TRoomGraphicsItem<PowerSpawnEntity> {
    typedef TRoomGraphicsItem<PowerSpawnEntity> _super;

    static const int SPAWN_ANIMATION_DURATION   = 3000;

public:
    RoomGraphicsItemPowerSpawn(const PowerSpawnEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemPowerSpawn();

private:
    PowerSpawnRenderer _powerSpawnRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const PowerSpawnEntity& current, const PowerSpawnEntity& updated) Q_DECL_OVERRIDE;
};


#endif // _ROOMGRAPHICSITEMPOWERSPAWN_H
