/*
 * File: RoomGraphicsItemLink.cpp
 * Created: 2019-1-15
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
#include <QPoint>

#include "RoomGraphicsItemLink.h"
#include "GraphicsItemEnergyBeam.h"
#include "../utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LinkEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LinkEntity::LinkEntity(const RoomEntity& entity)
    : _super(entity) {

}

QPoint LinkEntity::transferTarget() const {
    QJsonObject action;
    State currentState = getActionState(&action);
    Q_ASSERT(currentState == State_TransferingEnergy);

    return QPoint(getInt(action, "x"), getInt(action, "y"));
}

LinkEntity::State LinkEntity::getActionState(QJsonObject *pAction /* = nullptr */) const {
    State currentState = State_Idle;

    if(hasObject("actionLog")) {
        const QJsonObject actionLog = getObject("actionLog");
        QJsonObject action;

        if(!(action = JSONUtils::getObject(actionLog, "transferEnergy")).isEmpty ())
            currentState = State_TransferingEnergy;

        if(pAction != nullptr)
            *pAction = action;
    }

    return currentState;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemLink
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemLink::RoomGraphicsItemLink(const LinkEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Link, entity, cellSize, ItemZOrder_Link, parent),
      _linkRenderer(this),
      _glow(this) {

    _glow.setScale(GLOW_EFFECT_SCALE);
    _glow.setOpacity(GLOW_EFFECT_OPACITY);
    _glow.setVisible(entity.energy() > 0);

    _linkRenderer.setEnergy(entity.energy());
    _linkRenderer.setEnergyCapacity(entity.energyCapacity());
}

RoomGraphicsItemLink::~RoomGraphicsItemLink() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemLink::itemSize(const QSize& cellSize) const {
    return _linkRenderer.size(cellSize);
}

void RoomGraphicsItemLink::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _linkRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemLink::beginUpdate(const LinkEntity& current, const LinkEntity& updated) {

    if(current.energy() != updated.energy()) {
        _linkRenderer.setEnergy(updated.energy());
        _glow.setVisible(updated.energy() > 0);
    }

    if(current.energyCapacity() != updated.energyCapacity())
        _linkRenderer.setEnergyCapacity(updated.energyCapacity());

    if(current.state() != updated.state()) {
        if(updated.state () == LinkEntity::State_TransferingEnergy) {
            const QPointF source = centerPoint(itemEntity ().pos());
            const QPointF target = centerPoint(updated.transferTarget());

            GraphicsItemEnergyBeam::fire(scene(), source, target, GraphicsItemEnergyBeam::EnergyType_Energy, ItemZOrder_EnergyBeam);
        }
    }

    return _linkRenderer.isDirty();
}

//{
//    "_id": "5c328c71299a7f043e48ca96",
//    "actionLog": {
//        "transferEnergy": {
//            "x": 41,
//            "y": 8
//        }
//    },
//    "cooldown": 28,
//    "energy": 10,
//    "energyCapacity": 800,
//    "hits": 1000,
//    "hitsMax": 1000,
//    "notifyWhenAttacked": true,
//    "room": "W7N4",
//    "type": "link",
//    "user": "5c30b42b3ca96b042cc6228c",
//    "x": 12,
//    "y": 29
//}

