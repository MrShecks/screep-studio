/*
 * File: RoomGraphicsItemEnergy.h
 * Created: 2019-1-18
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

#ifndef _ROOMGRAPHICSITEMENERGY_H
#define _ROOMGRAPHICSITEMENERGY_H

#include "RoomGraphicsItem.h"
#include "ui/widgets/room/renderers/EnergyRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EnergyEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EnergyEntity : public RoomEntity {
    typedef RoomEntity _super;

public:
    EnergyEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    int energy() const                          { return getInt("energy"); }
    int energyCapacity() const                  { return Screeps::MAX_DROPPED_ENERGY; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemEnergy
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemEnergy : public TRoomGraphicsItem<EnergyEntity> {
    typedef TRoomGraphicsItem<EnergyEntity> _super;

public:
    RoomGraphicsItemEnergy(const EnergyEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemEnergy();

private:
    EnergyRenderer _energyRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const EnergyEntity& current, const EnergyEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMENERGY_H
