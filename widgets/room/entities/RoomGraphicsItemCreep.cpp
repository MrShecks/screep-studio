/*
 * File: RoomGraphicsItemCreep.cpp
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

#include <QPainter>
#include <QtMath>
#include <QMap>

#include "RoomGraphicsItemCreep.h"
#include "../../../utils/JSONUtils.h"

#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const RoomGraphicsItemCreep::TActionStateMap RoomGraphicsItemCreep::_ACTION_STATE_MAP = {
    { QStringLiteral("attack"),             State_Unknown },
    { QStringLiteral("attacked"),           State_Unknown },
    { QStringLiteral("build"),              State_Building },
    { QStringLiteral("harvest"),            State_Harvesting },
    { QStringLiteral("heal"),               State_Unknown },
    { QStringLiteral("healed"),             State_Unknown },
    { QStringLiteral("rangedAttack"),       State_Unknown },
    { QStringLiteral("rangedHeal"),         State_Unknown },
    { QStringLiteral("rangedMassAttack"),   State_Unknown },
    { QStringLiteral("repair"),             State_Repairing },
    { QStringLiteral("reserveController"),  State_Unknown },
    { QStringLiteral("say"),                State_SayingStuff },
    { QStringLiteral("upgradeController"),  State_Upgrading },
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreepEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CreepEntity::CreepEntity(const RoomEntity& entity)
    : _super(entity) {

    //_action = getObject("actionLog")
}

bool CreepEntity::isNpc() const {
    const int userId = getString("user").toInt();

    return userId == Screeps::USER_ID_INVADER || userId == Screeps::USER_ID_SOURCE_KEEPER;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemCreep
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemCreep::RoomGraphicsItemCreep(const CreepEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Creep, entity, cellSize, ItemZOrder_Creep, parent),
      _moveAnimation(new QPropertyAnimation(this)),
      _creepRenderer(this) {

    _moveAnimation->setTargetObject(this);
    _moveAnimation->setPropertyName("pos");
    _moveAnimation->setDuration(MOVE_DURATION);

    connect(_moveAnimation, &QPropertyAnimation::finished, this, &RoomGraphicsItemCreep::_onMovePosition);

    setTransformOriginPoint (boundingRect().center());

    Q_ASSERT_X(itemEntity().hasArray("body"), "RoomGraphicsItemCreep::RoomGraphicsItemCreep", "Creep JSON missing body array!");

    if(itemEntity ().hasArray("body")) {
        _creepRenderer.setJson(itemEntity().getArray("body"));
    }

    _creepRenderer.setNpc(entity.isNpc());
    _creepRenderer.setEnergy(entity.energy());
    _creepRenderer.setEnergyCapacity(entity.energyCapacity());

    _state = State_Idle;
}

RoomGraphicsItemCreep::~RoomGraphicsItemCreep() {

}

void RoomGraphicsItemCreep::lookAt(int x, int y) {
    _creepRenderer.setRotation(angleToRoomTarget(QPoint(x, y)));
    update();
}

//"actionLog": {
//    "attack": null,
//    "attacked": null,
//    "build": null,
//    "harvest": null,
//    "heal": null,
//    "healed": null,
//    "rangedAttack": null,
//    "rangedHeal": null,
//    "rangedMassAttack": null,
//    "repair": null,
//    "reserveController": null,
//    "say": null,
//    "upgradeController": null
//},

//
// https://docs.screeps.com/simultaneous-actions.html
//

#include <QJsonDocument>

RoomGraphicsItemCreep::State RoomGraphicsItemCreep::stateFromAction(const RoomEntity& updatedEntity, QJsonObject& action) const {
    static QMap<QString, State> ACTION_STATE_MAP = {
        { QStringLiteral("attack"), State_Unknown },
        { QStringLiteral("attacked"), State_Unknown },
        { QStringLiteral("build"), State_Building },
        { QStringLiteral("harvest"), State_Harvesting },
        { QStringLiteral("heal"), State_Unknown },
        { QStringLiteral("healed"), State_Unknown },
        { QStringLiteral("rangedAttack"), State_Unknown },
        { QStringLiteral("rangedHeal"), State_Unknown },
        { QStringLiteral("rangedMassAttack"), State_Unknown },
        { QStringLiteral("repair"), State_Repairing },
        { QStringLiteral("reserveController"), State_Unknown },
        { QStringLiteral("say"), State_SayingStuff },
        { QStringLiteral("upgradeController"), State_Upgrading },
    };

    State state = _state;

    if(updatedEntity.getBool("spawning"))
        state = State_Spawning;
    else if(updatedEntity.hasObject ("actionLog")) {    // Newly spawned creeps don't have "actionLog"
        QMap<QString, State>::const_iterator it = ACTION_STATE_MAP.constBegin();
        QMap<QString, State>::const_iterator limit = ACTION_STATE_MAP.constEnd();
        QJsonObject actionLog = updatedEntity.getObject("actionLog");

        for(; it != limit && action.isEmpty(); ++it) {
            if(JSONUtils::hasObject(actionLog, it.key()) && !actionLog[it.key()].isNull()) {
                action = actionLog[it.key()].toObject();
                state = it.value();
//#ifdef QT_DEBUG
//                if(state == State_Unknown)
//                    qDebug() << "Unknown State for action: Action=" << it.key();
//#endif // QT_DEBUG
            }
        }
    }

    return state;
}

RoomGraphicsItemCreep::State RoomGraphicsItemCreep::getState(const RoomEntity& current, const RoomEntity& updated, QJsonObject& action) const {
    State state = _state;

    if(updated.getBool("spawning"))
        state = State_Spawning;
    else if(updated.hasObject("actionLog")) {
        const QJsonObject actionLog = updated.getObject("actionLog");
        int count = 0;

        QJsonObject::const_iterator it = actionLog.constBegin();
        QJsonObject::const_iterator limit = actionLog.constEnd();

        for(; it != limit; ++it) {
            if(!it->isNull ()) {
                QJsonDocument doc(it->toObject());
                //qDebug() << "Action=" << it.key() << ", Data=" << doc.toJson (QJsonDocument::Compact);
                count++;
            }
        }

        //qDebug() << "Action action count=" << count;
        //Q_ASSERT(count <= 1);
    }

    return state;
}

void RoomGraphicsItemCreep::onStateChanged(State oldState, State newState, const QJsonObject& stateAction) {
    //qDebug() << "State Changed: Old State=" << oldState << ", New State=" << newState;

    switch(newState) {
        case State_Harvesting:             onStateHarvesting(oldState, stateAction);           break;
        case State_Upgrading:    onStateUpgradingControler(oldState, stateAction);   break;

        default: {

        }
        break;
    }
}

void RoomGraphicsItemCreep::onStateHarvesting(State oldState, const QJsonObject& stateAction) {
    int sourcePosX = JSONUtils::getInt(stateAction, "x");
    int sourcePosY = JSONUtils::getInt(stateAction, "y");

    lookAt(sourcePosX, sourcePosY);

    Q_UNUSED(oldState);
}

void RoomGraphicsItemCreep::onStateUpgradingControler(State oldState, const QJsonObject& stateAction) {
    int controllerPosX = JSONUtils::getInt(stateAction, "x");
    int controllerPosY = JSONUtils::getInt(stateAction, "y");

    lookAt(controllerPosX, controllerPosY);

    Q_UNUSED(oldState);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomGraphicsItemCreep::_onMovePosition() {
    if(!_moveQueue.isEmpty()) {
        const QPoint targetPos = _moveQueue.dequeue();

        _creepRenderer.setRotation(angleToRoomTarget(targetPos));

        _moveAnimation->setStartValue(pos());
        _moveAnimation->setEndValue(roomToScene(targetPos));
        _moveAnimation->start();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemCreep::itemSize(const QSize& cellSize) const {
    return _creepRenderer.size(cellSize);
}

void RoomGraphicsItemCreep::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _creepRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemCreep::beginUpdate(const CreepEntity& current, const CreepEntity& updated) {
    QJsonObject dummyAction;
    State tempState = getState (current, updated, dummyAction);

    if(current.pos() != updated.pos()) {
        _moveQueue.enqueue(QPoint(updated.posX(), updated.posY()));

        if(_moveAnimation->state() != QPropertyAnimation::Running)
            _onMovePosition();

    }

    State newState;
    QJsonObject stateAction;

    if((newState = stateFromAction(updated, stateAction)) != _state) {
        onStateChanged(_state, newState, stateAction);
        _state = newState;
    }

    if(current.energy() != updated.energy())
        _creepRenderer.setEnergy(updated.energy());

    if(current.energyCapacity() != updated.energyCapacity())
        _creepRenderer.setEnergyCapacity(updated.energyCapacity());

    return _creepRenderer.isDirty();
}
