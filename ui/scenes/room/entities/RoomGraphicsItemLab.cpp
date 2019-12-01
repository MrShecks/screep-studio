/*
 * File: RoomGraphicsItemLab.cpp
 * Created: 2019-1-22
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

#include <QPainter>

#include "RoomGraphicsItemLab.h"
#include "GraphicsItemEnergyBeam.h"
#include "utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LabEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LabEntity::LabEntity(const RoomEntity& entity)
    : _super(entity),
      _state(State_Idle) {

    if(hasObject("actionLog")) {
        const QJsonObject actionLog = getObject("actionLog");

        if(!(_action = JSONUtils::getObject(actionLog, "runReaction")).isEmpty ())
            _state = State_Reacting;
    }
}

QPoint LabEntity::reactionSource() const {
    Q_ASSERT(_state == State_Reacting);
    return QPoint(JSONUtils::getInt(_action, "x1"), JSONUtils::getInt(_action, "y1"));
}

QPoint LabEntity::reactionTarget() const {
    Q_ASSERT(_state == State_Reacting);
    return QPoint(JSONUtils::getInt(_action, "x2"), JSONUtils::getInt(_action, "y2"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemLab
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemLab::RoomGraphicsItemLab(const LabEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Lab, entity, cellSize, ItemZOrder_Lab, parent),
      _labRenderer(this) {

    _labRenderer.setEnergy(entity.energy());
    _labRenderer.setEnergyCapacity(entity.energyCapacity());
}

RoomGraphicsItemLab::~RoomGraphicsItemLab() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemLab::itemSize(const QSize& cellSize) const {
    return _labRenderer.size(cellSize);
}

void RoomGraphicsItemLab::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _labRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemLab::beginUpdate(const LabEntity& current, const LabEntity& updated) {

    if(current.energy() != updated.energy())
        _labRenderer.setEnergy(updated.energy());

    if(current.energyCapacity() != updated.energyCapacity())
        _labRenderer.setEnergyCapacity(updated.energyCapacity());

    if(current.state() != updated.state() && updated.state() == LabEntity::State_Reacting) {
        GraphicsItemEnergyBeam::fire(scene(), centerPoint(updated.reactionSource()), centerPoint(updated.reactionTarget()), GraphicsItemEnergyBeam::EnergyType_Resource, ItemZOrder_EnergyBeam);
    }

    return _labRenderer.isDirty();
}

//
//{
//    "_id": "5b6df83854c0a0179f489002",
//    "actionLog": {
//        "runReaction": {
//            "x1": 27,                 // I think these are the start and end co-ordinates
//            "x2": 28,                 // of the energy beam line to be drawn
//            "y1": 28,
//            "y2": 29
//        }
//    },
//    "cooldown": 19,
//    "energy": 1680,
//    "energyCapacity": 2000,
//    "hits": 500,
//    "hitsMax": 500,
//    "mineralAmount": 75,
//    "mineralCapacity": 3000,
//    "mineralType": "OH",
//    "notifyWhenAttacked": false,
//    "room": "W31S32",
//    "type": "lab",
//    "user": "59c59c8c3530f447c0aca65f",
//    "x": 26,
//    "y": 29
//}
//
