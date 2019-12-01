/*
 * File: RoomGraphicsItemController.h
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

#ifndef _ROOMGRAPHICSITEMCONTROLLER_H
#define _ROOMGRAPHICSITEMCONTROLLER_H

#include "RoomGraphicsItem.h"
#include "GraphicsItemGlow.h"
#include "ui/widgets/room/renderers/ControllerRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ControllerEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ControllerEntity : public RoomEntity {
    typedef RoomEntity _super;

public:
    ControllerEntity(const RoomEntity& entity)
        : _super(entity) {
    }

    int level() const                           { return getInt("level"); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemSpawn
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemController : public TRoomGraphicsItem<ControllerEntity> {
    typedef TRoomGraphicsItem<ControllerEntity> _super;

    static constexpr qreal GLOW_EFFECT_SCALE        = 0.8;
    static constexpr qreal GLOW_EFFECT_OPACITY_MIN  = 0.2;
    static constexpr qreal GLOW_EFFECT_OPACITY_MAX  = 0.9;

public:
    RoomGraphicsItemController(const ControllerEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemController();

private:
    ControllerRenderer _controllerRenderer;
    GraphicsItemGlow _glow;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const ControllerEntity& current, const ControllerEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMCONTROLLER_H
