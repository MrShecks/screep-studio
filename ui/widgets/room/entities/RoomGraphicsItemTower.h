/*
 * File: RoomGraphicsItemTower.h
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

#ifndef _ROOMGRAPHICSITEMTOWER_H
#define _ROOMGRAPHICSITEMTOWER_H

#include <QPropertyAnimation>
#include <QTimer>

#include "RoomGraphicsItem.h"
#include "GraphicsItemGlow.h"
#include "GraphicsItemEnergyBeam.h"
#include "ui/widgets/room/renderers/TowerRenderer.h"

//{
//    "_id": "5bad769f3686861efc4ccc44",
//    "actionLog": {
//        "attack": null,
//        "heal": null,
//        "repair": null
//    },
//    "hits": 3000,
//    "hitsMax": 3000,
//    "notifyWhenAttacked": true,
//    "room": "W19S47",
//    "store": {
//        "energy": 1000
//    },
//    "storeCapacityResource": {
//        "energy": 1000
//    },
//    "type": "tower",
//    "user": "5b1d1c9e340d195a66436301",
//    "x": 29,
//    "y": 33
//}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TowerEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TowerEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:
    enum State {
        State_Unknown                           = -1,

        State_Idle,
        State_Healing,
        State_Repairing,
        State_Attacking
    };

    TowerEntity(const RoomEntity& entity)
        : _super(entity) {
    }

    State state() const                 { return getActionState(); }

    int energy() const                  { return getStoredResourceAmount("energy"); }
    int energyCapacity() const          { return getStoredResourceCapacity("energy"); }

    QPoint target() const;

private:
    State getActionState(QJsonObject* pAction = nullptr) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemTower
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemTower : public TRoomGraphicsItem<TowerEntity> {
    typedef TRoomGraphicsItem<TowerEntity> _super;

    Q_OBJECT
    Q_PROPERTY(qreal turretRotation READ turretRotation WRITE setTurretRotation)

    static const int IDLE_ANIMATION_DURATION    = 1000 * 15;

    static constexpr qreal GLOW_EFFECT_SCALE    = 1.5;
    static constexpr qreal GLOW_EFFECT_OPACITY  = 0.5;

public:
    RoomGraphicsItemTower(const TowerEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemTower();

    qreal turretRotation() const;
    void setTurretRotation(qreal turretRotation);

private:
    TowerRenderer _towerRenderer;
    GraphicsItemGlow _glow;
    QPropertyAnimation _idleAnimation;

    void fire(GraphicsItemEnergyBeam::EnergyType type, const QPoint& roomTarget);

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const TowerEntity& current, const TowerEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMTOWER_H
