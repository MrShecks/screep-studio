/*
 * File: RoomGraphicsItemObserver.cpp
 * Created: 2019-2-1
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

#include "RoomGraphicsItemObserver.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemObserver
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemObserver::RoomGraphicsItemObserver(const ObserverEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Observer, entity, cellSize, ItemZOrder_Observer, parent),
      _observerRenderer(this),
      _eyeRotation(0) {

    // Just a simple smooth rotation. The official client moves
    // from 0, 90, 180, 270 degrees with a pause in between each
    // position. Could do this with an annimation group but I
    // kind of prefer this simple animation :)

    _rotateAnimation.setTargetObject(this);
    _rotateAnimation.setPropertyName("eyeRotation");
    _rotateAnimation.setStartValue(0);
    _rotateAnimation.setEndValue(360);
    _rotateAnimation.setDuration(EYE_ROTATE_DURATION);
    _rotateAnimation.setLoopCount(-1);
    _rotateAnimation.start();
}

RoomGraphicsItemObserver::~RoomGraphicsItemObserver() {

}

qreal RoomGraphicsItemObserver::eyeRotation() const {
    return _observerRenderer.eyeRotation();
}

void RoomGraphicsItemObserver::setEyeRotation(qreal eyeRotation) {
    _observerRenderer.setEyeRotation(eyeRotation);
    update();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemObserver::itemSize(const QSize& cellSize) const {
    return _observerRenderer.size(cellSize);
}

void RoomGraphicsItemObserver::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _observerRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemObserver::beginUpdate(const ObserverEntity& current, const ObserverEntity& updated) {

    return _observerRenderer.isDirty();
}

