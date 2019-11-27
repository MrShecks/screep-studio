/*
 * File: GraphicsItemGlow.h
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

#ifndef GRAPHICSITEMGLOW_H
#define GRAPHICSITEMGLOW_H

#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QGraphicsEffect>
#include <QPainter>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphicsColorizeEffect
// Custom QGraphicsColorizeEffect that allows setting the paint composition mode
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GraphicsColorizeEffect : public QGraphicsColorizeEffect {
    typedef QGraphicsColorizeEffect _super;

public:
    GraphicsColorizeEffect(QObject* parent = nullptr)
        : _super(parent), _compositionMode(QPainter::CompositionMode_SourceOver) {

    }

    virtual ~GraphicsColorizeEffect() {

    }

    void setCompositionMode(QPainter::CompositionMode compositionMode) {
        _compositionMode = compositionMode;
    }

protected:
    void draw(QPainter *painter) {
        QPainter::CompositionMode compositionMode = painter->compositionMode();

        painter->setCompositionMode(_compositionMode);
        _super::draw(painter);
        painter->setCompositionMode(compositionMode);
    }

private:
    QPainter::CompositionMode _compositionMode;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphicsItemGlow
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GraphicsItemGlow : public QObject, public QGraphicsPixmapItem {
    typedef QGraphicsPixmapItem _super;

    Q_OBJECT
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)

    static const QColor DEF_GLOW_COLOR;

public:
    static const int _MIN_ANIMATION_FRAMES  = 4;

    GraphicsItemGlow(QGraphicsItem* parent);
    virtual ~GraphicsItemGlow();

    bool isAnimated() const;

    void setColor(const QColor& color);
    void setGlowAnimation(qreal opacityFrom, qreal opacityTo, int duration);
    void setFlickerAnimation(qreal opacityFrom, qreal opacityTo, int duration, int frames = _MIN_ANIMATION_FRAMES);

    void setCompositionMode(QPainter::CompositionMode compositionMode);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant& value) Q_DECL_OVERRIDE;

private:
    QPropertyAnimation _opacityAnimator;
    GraphicsColorizeEffect _colorizeEffect;

    void centreInParent(const QRectF& parentRect, qreal scale);
};

#endif // GRAPHICSITEMGLOW_H
