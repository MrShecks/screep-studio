/*
 * File: RoomGraphicsItemObserver.h
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

#ifndef _ROOMGRAPHICSITEMOBSERVER_H
#define _ROOMGRAPHICSITEMOBSERVER_H

#include <QPropertyAnimation>

#include "RoomGraphicsItem.h"
#include "ui/widgets/room/renderers/ObserverRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ObserverEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ObserverEntity : public RoomEntity {
    typedef RoomEntity _super;

public:
    ObserverEntity(const RoomEntity& entity)
        : _super(entity) {

    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemObserver
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemObserver : public TRoomGraphicsItem<ObserverEntity> {
    typedef TRoomGraphicsItem<ObserverEntity> _super;

    Q_OBJECT
    Q_PROPERTY(qreal eyeRotation READ eyeRotation WRITE setEyeRotation)

    static const int EYE_ROTATE_DURATION        = (1000 * 2);

public:
    RoomGraphicsItemObserver(const ObserverEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemObserver();

    qreal eyeRotation() const;
    void setEyeRotation(qreal eyeRotation);

private:
    QPropertyAnimation _rotateAnimation;
    ObserverRenderer _observerRenderer;
    qreal _eyeRotation;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const ObserverEntity& current, const ObserverEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMOBSERVER_H
