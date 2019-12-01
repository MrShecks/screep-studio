/*
 * File: RoomGraphicsItemSource.h
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

#ifndef _ROOMGRAPHICSITEMSOURCE_H
#define _ROOMGRAPHICSITEMSOURCE_H

#include "RoomGraphicsItem.h"
#include "GraphicsItemGlow.h"
#include "ui/widgets/room/renderers/SourceRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SourceEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SourceEntity : public RoomEntity {
    typedef RoomEntity _super;

public:
    SourceEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    int energy() const                  { return getInt("energy"); }
    int energyCapacity() const          { return getInt("energyCapacity"); }

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemSource
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemSource : public TRoomGraphicsItem<SourceEntity> {
    typedef TRoomGraphicsItem<SourceEntity> _super;

    static constexpr qreal GLOW_EFFECT_SCALE        = 2.0;
    static constexpr qreal GLOW_EFFECT_OPACITY_MIN  = 0.2;
    static constexpr qreal GLOW_EFFECT_OPACITY_MAX  = 0.7;

public:
    RoomGraphicsItemSource(const SourceEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemSource();

private:
    SourceRenderer _sourceRenderer;
    GraphicsItemGlow _glow;

    int energy() const;
    int energyCapacity() const;

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const SourceEntity& current, const SourceEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMSOURCE_H
