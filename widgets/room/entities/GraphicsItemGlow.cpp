/*
 * File: GraphicsItemGlow.cpp
 * Created: 2019-1-1
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


#include <QRandomGenerator>
#include <QtGlobal>

#include "GraphicsItemGlow.h"

#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor GraphicsItemGlow::DEF_GLOW_COLOR   = QColor("#ffffff");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphicsItemGlow
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GraphicsItemGlow::GraphicsItemGlow(QGraphicsItem* parent)
    : _super(QPixmap(":/assets/images/glow.png"), parent),
      _opacityAnimator(this) {
    Q_ASSERT(parent != nullptr);

    setFlag(ItemStacksBehindParent, true);
    setFlag(ItemSendsGeometryChanges, true);

    _colorizeEffect.setColor(DEF_GLOW_COLOR);
    _colorizeEffect.setCompositionMode(QPainter::CompositionMode_Overlay);

    setGraphicsEffect(&_colorizeEffect);
}

GraphicsItemGlow::~GraphicsItemGlow() {

}

bool GraphicsItemGlow::isAnimated() const {
    return _opacityAnimator.state () == QPropertyAnimation::Running;
}

void GraphicsItemGlow::setColor(const QColor& color) {
    _colorizeEffect.setColor(color);
}

void GraphicsItemGlow::setGlowAnimation(qreal opacityFrom, qreal opacityTo, int duration) {
    if(_opacityAnimator.state() == QPropertyAnimation::Running)
        _opacityAnimator.stop();

    _opacityAnimator.setTargetObject(this);
    _opacityAnimator.setPropertyName("opacity");
    _opacityAnimator.setDuration(duration);

    _opacityAnimator.setKeyValues (QPropertyAnimation::KeyValues());

    _opacityAnimator.setKeyValueAt (0.0, opacityFrom);
    _opacityAnimator.setKeyValueAt (0.5, opacityTo);
    _opacityAnimator.setKeyValueAt (1.0, opacityFrom);
    _opacityAnimator.setLoopCount (-1);
    _opacityAnimator.start();
}

void GraphicsItemGlow::setFlickerAnimation(qreal opacityFrom, qreal opacityTo, int duration, int frames) {

    if(frames < _MIN_ANIMATION_FRAMES)
        frames = _MIN_ANIMATION_FRAMES;

    if(_opacityAnimator.state() == QPropertyAnimation::Running)
        _opacityAnimator.stop();

    _opacityAnimator.setTargetObject(this);
    _opacityAnimator.setPropertyName("opacity");
    _opacityAnimator.setDuration(duration);

    _opacityAnimator.setKeyValues (QPropertyAnimation::KeyValues());
    _opacityAnimator.setEasingCurve (QEasingCurve::InOutBounce);
    _opacityAnimator.setLoopCount(-1);

    qreal step = 1.0f / (frames + 2);
    qreal key = step;

    _opacityAnimator.setStartValue(opacityFrom);
    _opacityAnimator.setEndValue(opacityTo);

    for(int frame = 0; frame < frames; ++frame) {
        qreal value = (opacityTo - opacityFrom) * QRandomGenerator::global()->generateDouble();

        _opacityAnimator.setKeyValueAt(key, value);

        //qDebug() << "Adding Key=" << key << ", Value=" << value;

        key += step;
    }

    _opacityAnimator.start();
}

void GraphicsItemGlow::setCompositionMode(QPainter::CompositionMode compositionMode) {
    _colorizeEffect.setCompositionMode(compositionMode);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QVariant GraphicsItemGlow::itemChange(GraphicsItemChange change, const QVariant& value) {
    QGraphicsItem* p;

    if((p = parentItem()) != nullptr) {
        const QRectF parentRect = p->boundingRect();

        if(change == ItemSceneHasChanged && !value.isNull()) {
            centreInParent(parentRect, scale());
        } else if(change == ItemScaleHasChanged) {
            centreInParent(parentRect, value.toReal());
        }
    }

    return _super::itemChange(change, value);
}

void GraphicsItemGlow::centreInParent(const QRectF& parentRect, qreal scale) {
    const int width = pixmap().width() * scale;
    const int height = pixmap().height() * scale;

    setPos(parentRect.center().x() - width / 2, parentRect.center().y() - height / 2);
}
