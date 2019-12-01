/*
 * File: RoomGraphicsItemTombstone.h
 * Created: 2018-12-29
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

#ifndef _ROOMGRAPHICSITEMTOMBSTONE_H
#define _ROOMGRAPHICSITEMTOMBSTONE_H

#include "RoomGraphicsItem.h"
#include "ui/scenes/room/renderers/TombstoneRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TombstoneEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TombstoneEntity : public RoomEntity {
    typedef RoomEntity _super;

public:
    TombstoneEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    int decayTime() const                       { return getInt("decayTime"); }
    int deathTime() const                       { return getInt("deathTime"); }

    int getTotalResources() const {
        int totalResources = 0;

        for(const QString& resourceName : Screeps::RESOURCES_ALL)
            totalResources += getInt(resourceName, 0);

        return totalResources;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemTombstone
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemTombstone : public TRoomGraphicsItem<TombstoneEntity> {
    typedef TRoomGraphicsItem<TombstoneEntity> _super;

public:
    RoomGraphicsItemTombstone(const TombstoneEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemTombstone();

private:
    TombstoneRenderer _tombstoneRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const TombstoneEntity& current, const TombstoneEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMTOMBSTONE_H
