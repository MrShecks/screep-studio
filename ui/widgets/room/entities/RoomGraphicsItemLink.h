/*
 * File: RoomGraphicsItemLink.h
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

#ifndef _ROOMGRAPHICSITEMLINK_H
#define _ROOMGRAPHICSITEMLINK_H

#include "RoomGraphicsItem.h"
#include "GraphicsItemGlow.h"
#include "../renderers/LinkRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LinkEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LinkEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:

    enum State {
        State_Idle,
        State_TransferingEnergy
    };

    LinkEntity(const RoomEntity& entity);

    State state() const                 { return getActionState(); }

    int energy() const                  { return getStoredResourceAmount("energy"); }
    int energyCapacity() const          { return getStoredResourceCapacity("energy"); }

    QPoint transferTarget() const;

private:
    State getActionState(QJsonObject *pAction = nullptr) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemLink
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemLink : public TRoomGraphicsItem<LinkEntity> {
    typedef TRoomGraphicsItem<LinkEntity> _super;

    static constexpr qreal GLOW_EFFECT_SCALE    = 1.5;
    static constexpr qreal GLOW_EFFECT_OPACITY  = 0.2;

public:
    RoomGraphicsItemLink(const LinkEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemLink();

private:
    LinkRenderer _linkRenderer;
    GraphicsItemGlow _glow;

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const LinkEntity& current, const LinkEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMLINK_H
