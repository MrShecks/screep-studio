/*
 * File: RoomGraphicsItemCreep.h
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

#ifndef _ROOMGRAPHICSITEMCREEP_H
#define _ROOMGRAPHICSITEMCREEP_H

#include <QPropertyAnimation>
#include <QQueue>

#include "RoomGraphicsItem.h"
#include "ui/widgets/room/renderers/CreepRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreepEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//const RoomGraphicsItemCreep::TActionStateMap RoomGraphicsItemCreep::_ACTION_STATE_MAP = {
//    { QStringLiteral("attack"),             State_Unknown },
//    { QStringLiteral("attacked"),           State_Unknown },
//    { QStringLiteral("build"),              State_Building },
//    { QStringLiteral("harvest"),            State_Harvesting },
//    { QStringLiteral("heal"),               State_Unknown },
//    { QStringLiteral("healed"),             State_Unknown },
//    { QStringLiteral("rangedAttack"),       State_Unknown },
//    { QStringLiteral("rangedHeal"),         State_Unknown },
//    { QStringLiteral("rangedMassAttack"),   State_Unknown },
//    { QStringLiteral("repair"),             State_Repairing },
//    { QStringLiteral("reserveController"),  State_Unknown },
//    { QStringLiteral("say"),                State_SayingStuff },
//    { QStringLiteral("upgradeController"),  State_Upgrading },
//};

class CreepEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:
    enum Action {

        Action_Heal                             = 1 << 0,
        Action_Build                            = 1 << 1,
        Action_Repair                           = 1 << 2,
        Action_Harvest                          = 1 << 3,
        Action_Attack                           = 1 << 4,

        Action_Healed                           = 1 << 5,
        Action_Attacked                         = 1 << 6,

        Action_Ranged_Attack                    = 1 << 7,
        Action_Ranged_Heal                      = 1 << 8,
        Action_Ranged_Mass_Attack               = 1 << 9,

        Action_Reserve_Controller               = 1 << 10,
        Action_Upgrade_Controller               = 1 << 11,

        Action_Say                              = 1 << 12
    };

    CreepEntity(const RoomEntity& entity);

    int energy() const                          { return getStoredResourceAmount("energy"); }
    int energyCapacity() const                  { return getStoreCapacity(); }

    bool isNpc() const;

    QPoint target() const;

private:
    QJsonObject _action;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemCreep
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemCreep : public TRoomGraphicsItem<CreepEntity> {
    typedef TRoomGraphicsItem<CreepEntity> _super;

    static const int MOVE_DURATION              = 1000;

    enum State {
        State_Unknown                           = -1,

        State_Idle,
        State_Moving,
        State_Spawning,
        State_Building,
        State_Repairing,
        State_Harvesting,
        State_SayingStuff,
        State_Upgrading
    };

public:
    RoomGraphicsItemCreep(const CreepEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemCreep();

private slots:
    void _onMovePosition();

private:
    typedef QHash<QString, State> TActionStateMap;
    typedef QQueue<QPoint> TMoveQueue;

    QPropertyAnimation* _moveAnimation;
    TMoveQueue _moveQueue;

    CreepRenderer _creepRenderer;
    State _state;

    static const TActionStateMap _ACTION_STATE_MAP;

    void lookAt(int x, int y);

    State stateFromAction(const RoomEntity& updatedEntity, QJsonObject& action) const;
    State getState(const RoomEntity& current, const RoomEntity& updated, QJsonObject& action) const;

    void onStateChanged(State oldState, State newState, const QJsonObject& stateAction);

    void onStateHarvesting(State oldState, const QJsonObject& stateAction);
    void onStateUpgradingControler(State oldState, const QJsonObject& stateAction);

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const CreepEntity& current, const CreepEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMCREEP_H
