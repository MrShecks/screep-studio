/*
 * File: RoomGraphicsItemExtractor.cpp
 * Created: 2019-1-9
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
#include "RoomGraphicsItemExtractor.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemExtractor
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemExtractor::RoomGraphicsItemExtractor(const ExtractorEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Extractor, entity, cellSize, ItemZOrder_Extractor, parent),
      _extractorRenderer(this),
      _rotationAnimator(this) {

    _rotationAnimator.setTargetObject(this);
    _rotationAnimator.setPropertyName("extractorRotation");
    _rotationAnimator.setDuration(ROTATE_ANIMATION_DURATION);
    _rotationAnimator.setLoopCount(-1);
    _rotationAnimator.setStartValue(0);
    _rotationAnimator.setEndValue(360);

    if(entity.cooldown())
        _rotationAnimator.start();
}

RoomGraphicsItemExtractor::~RoomGraphicsItemExtractor() {

}

qreal RoomGraphicsItemExtractor::extractorRotation() const {
    return _extractorRenderer.rotation();
}

void RoomGraphicsItemExtractor::setExtractorRotation(qreal extractorRotation) {
    _extractorRenderer.setRotation (extractorRotation);
    update();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemExtractor::itemSize(const QSize& cellSize) const {
    return _extractorRenderer.size(cellSize);
}

void RoomGraphicsItemExtractor::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _extractorRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemExtractor::beginUpdate(const ExtractorEntity& current, const ExtractorEntity& updated) {

    if(current.cooldown() != updated.cooldown()) {
        if(updated.cooldown() <= 0 && _rotationAnimator.state() == QPropertyAnimation::Running)
            _rotationAnimator.pause();
        else if(_rotationAnimator.state() != QPropertyAnimation::Running) {
            switch(_rotationAnimator.state()) {
                case QPropertyAnimation::Stopped:   _rotationAnimator.start();      break;
                case QPropertyAnimation::Paused:    _rotationAnimator.resume();     break;

                default:
                break;
            }
        }
    }

    // Repainting of the graphics item will be triggered from setExtractorRotation() when the rotation
    // animation is running so we can just return false here.

    return false;
}
