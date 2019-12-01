/*
 * File: RoomGraphicsItemTower.cpp
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

#include <QPainter>
#include <QRandomGenerator>

#include "RoomGraphicsItemTower.h"
#include "GraphicsItemEnergyBeam.h"
#include "utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TowerEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QPoint TowerEntity::target() const {
    QJsonObject action;
    State currentState = getActionState(&action);
    Q_ASSERT_X(currentState > State_Idle, "TowerEntity::target", "Target not available in current state.");

    return QPoint(getInt(action, "x", -1), getInt(action, "y", -1));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TowerEntity::State TowerEntity::getActionState(QJsonObject *pAction /* = nullptr */) const {
    State currentState = State_Unknown;

    if(hasObject("actionLog")) {
        const QJsonObject actionLog = getObject("actionLog");
        QJsonObject action;

        if(!(action = JSONUtils::getObject(actionLog, "heal")).isEmpty ())
            currentState = State_Healing;
        else if(!(action = JSONUtils::getObject(actionLog, "repair")).isEmpty ())
            currentState = State_Repairing;
        else if(!(action = JSONUtils::getObject(actionLog, "attack")).isEmpty ())
            currentState = State_Attacking;
        else
            currentState = State_Idle;

        if(pAction != nullptr)
            *pAction = action;
    }

    return currentState;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemTower
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemTower::RoomGraphicsItemTower(const TowerEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Tower, entity, cellSize, ItemZOrder_Tower, parent),
      _towerRenderer(this),
      _glow(this),
      _idleAnimation(this) {

    _towerRenderer.setEnergy(entity.energy());
    _towerRenderer.setEnergyCapacity(entity.energyCapacity());

    _idleAnimation.setTargetObject(this);
    _idleAnimation.setPropertyName("turretRotation");
    _idleAnimation.setDuration(IDLE_ANIMATION_DURATION);
    _idleAnimation.setLoopCount(-1);
    _idleAnimation.setStartValue(QRandomGenerator::global()->bounded(0, 360));
    _idleAnimation.setEndValue(_idleAnimation.startValue().toInt() + 360);

    _idleAnimation.start();

    _glow.setScale(GLOW_EFFECT_SCALE);
    _glow.setOpacity(GLOW_EFFECT_OPACITY);
}

RoomGraphicsItemTower::~RoomGraphicsItemTower() {

}

qreal RoomGraphicsItemTower::turretRotation() const {
    return _towerRenderer.rotation();
}

void RoomGraphicsItemTower::setTurretRotation(qreal turretRotation) {
    _towerRenderer.setRotation(turretRotation);
    update();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemTower::itemSize(const QSize& cellSize) const {
    return _towerRenderer.size(cellSize);
}

void RoomGraphicsItemTower::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _towerRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RoomGraphicsItemTower::beginUpdate(const TowerEntity& current, const TowerEntity& updated) {

    if(current.state() != updated.state()) {

        //
        // Transitions from previous state
        //

        switch(current.state()) {
            case TowerEntity::State_Idle: {
                _idleAnimation.stop();
            }
            break;

            default:
            break;
        }

        //
        // Transitions to new state
        //

        switch(updated.state()) {
            case TowerEntity::State_Idle: {
                _idleAnimation.setStartValue(turretRotation());
                _idleAnimation.setEndValue(turretRotation() + 360);
                _idleAnimation.start();
            }
            break;

            default:
            break;
        }
    }

    switch(updated.state()) {
        case TowerEntity::State_Healing:     fire(GraphicsItemEnergyBeam::EnergyType_Heal, updated.target());      break;
        case TowerEntity::State_Repairing:   fire(GraphicsItemEnergyBeam::EnergyType_Repair, updated.target());    break;
        case TowerEntity::State_Attacking:   fire(GraphicsItemEnergyBeam::EnergyType_Attack, updated.target());    break;

        default: {

        }
        break;
    }

    if(current.energy() != updated.energy())
        _towerRenderer.setEnergy(updated.energy());

    if(current.energyCapacity() != updated.energyCapacity())
        _towerRenderer.setEnergyCapacity(updated.energyCapacity());

    return _towerRenderer.isDirty();
}

void RoomGraphicsItemTower::fire(GraphicsItemEnergyBeam::EnergyType type, const QPoint& roomTarget) {
    const QPoint target = centerPoint(roomTarget);
    const QPoint source = centerPoint(itemEntity ().pos());
    const qreal rotation = angleToSceneTarget(target);

    if(turretRotation () != rotation)
        setTurretRotation(rotation);

    GraphicsItemEnergyBeam::fire(scene(), source, target, type, ItemZOrder_EnergyBeam);
}

//
// Game.getObjectById('5c226e9dc7a8e50421aeffda').heal(Game.creeps.h2)
// Game.getObjectById('5c226e9dc7a8e50421aeffda').attack(Game.creeps.h2)
// require('main').markTarget('u1')
//{
//    "_id": "5c226e9dc7a8e50421aeffda",
//    "actionLog": {
//        "attack": null,
//        "heal": null,
//        "repair": null
//    },
//    "energy": 1000,
//    "energyCapacity": 1000,
//    "hits": 3000,
//    "hitsMax": 3000,
//    "notifyWhenAttacked": true,
//    "room": "W8N3",
//    "type": "tower",
//    "user": "5c219cbd6edd010419f53a3a",
//    "x": 21,
//    "y": 15
//}
//

// storage.db['rooms.objects'].update({ _id: '1bc30772347c388' },{ $set: { level: 5 }})
// storage.db['rooms.objects'].update({ _id: '5c29758e91b9590417189318' },{ $set: { progress: 4900 }})

//{
//    "_id": "5c2a50ff855067041e7f1c97",
//    "name": null,
//    "progress": 0,
//    "progressTotal": 5000,
//    "room": "W8N3",
//    "structureType": "tower",
//    "type": "constructionSite",
//    "user": "5c219cbd6edd010419f53a3a",
//    "x": 37,
//    "y": 8
//}

//{
//    "_id": "5c2a50f8855067041e7f1c96",
//    "name": null,
//    "progress": 0,
//    "progressTotal": 5000,
//    "room": "W8N3",
//    "structureType": "tower",
//    "type": "constructionSite",
//    "user": "5c219cbd6edd010419f53a3a",
//    "x": 12,
//    "y": 34
//}

//{
//    "_id": "5c29758e91b9590417189318",
//    "name": null,
//    "progress": 0,
//    "progressTotal": 5000,
//    "room": "W8N3",
//    "structureType": "tower",
//    "type": "constructionSite",
//    "user": "5c219cbd6edd010419f53a3a",
//    "x": 36,
//    "y": 28
//}


