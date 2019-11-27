/*
 * File: RoomGraphicsItemMineral.h
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

#ifndef _ROOMGRAPHICSITEMMINERAL_H
#define _ROOMGRAPHICSITEMMINERAL_H

#include "RoomGraphicsItem.h"
#include "GraphicsItemGlow.h"
#include "../renderers/MineralRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MineralEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MineralEntity : public RoomEntity {
    typedef RoomEntity _super;

public:

    MineralEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    QString mineralType() const                 { return getString("mineralType", "?"); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemMineral
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemMineral : public TRoomGraphicsItem<MineralEntity> {
    typedef TRoomGraphicsItem<MineralEntity> _super;

    static constexpr qreal GLOW_EFFECT_SCALE        = 1.5;
    static constexpr qreal GLOW_EFFECT_OPACITY_MIN  = 0.5;
    static constexpr qreal GLOW_EFFECT_OPACITY_MAX  = 0.9;

public:
    RoomGraphicsItemMineral(const MineralEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemMineral();

private:
    MineralRenderer _mineralRenderer;
    GraphicsItemGlow _glow;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMMINERAL_H
