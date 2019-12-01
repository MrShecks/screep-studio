/*
 * File: RoomGraphicsItemUnknown.h
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

#ifndef _ROOMGRAPHICSITEMUNKNOWN_H
#define _ROOMGRAPHICSITEMUNKNOWN_H

#include "RoomGraphicsItem.h"
#include "../renderers/UnknownRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemUnknown
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemUnknown : public TRoomGraphicsItem<RoomEntity> {
    typedef TRoomGraphicsItem<RoomEntity> _super;

public:
    RoomGraphicsItemUnknown(const RoomEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemUnknown();

private:
    UnknownRenderer _unknownRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMUNKNOWN_H
