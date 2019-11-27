/*
 * File: RoomGraphicsItemNuker.h
 * Created: 2019-1-23
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

#ifndef _ROOMGRAPHICSITEMNUKER_H
#define _ROOMGRAPHICSITEMNUKER_H


#include "RoomGraphicsItem.h"
#include "../renderers/NukerRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NukerEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NukerEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:
    NukerEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    int energy() const                          { return getStoredResourceAmount("energy"); }
    int energyCapacity() const                  { return getStoredResourceCapacity("energy"); }

    int resources() const                       { return getStoredResourceAmount("G"); }
    int resourceCapacity() const                { return getStoredResourceCapacity("G"); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemNuker
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemNuker : public TRoomGraphicsItem<NukerEntity> {
    typedef TRoomGraphicsItem<NukerEntity> _super;

public:
    RoomGraphicsItemNuker(const NukerEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemNuker();

private:
    NukerRenderer _nukerRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const NukerEntity& current, const NukerEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMNUKER_H
