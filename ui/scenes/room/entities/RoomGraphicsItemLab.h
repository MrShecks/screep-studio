/*
 * File: RoomGraphicsItemLab.h
 * Created: 2019-1-22
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

#ifndef _ROOMGRAPHICSITEMLAB_H
#define _ROOMGRAPHICSITEMLAB_H

#include "RoomGraphicsItem.h"
#include "ui/scenes/room/renderers/LabRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LabEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LabEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:
    enum State {
        State_Idle,
        State_Reacting
    };

    LabEntity(const RoomEntity& entity);

    State state() const                         { return _state; }

    int energy() const                          { return getStoredResourceAmount("energy"); }
    int energyCapacity() const                  { return getStoredResourceAmount ("energy"); }

    QPoint reactionSource() const;
    QPoint reactionTarget() const;

private:
    State _state;
    QJsonObject _action;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemLab
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemLab : public TRoomGraphicsItem<LabEntity> {
    typedef TRoomGraphicsItem<LabEntity> _super;

public:
    RoomGraphicsItemLab(const LabEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemLab();

private:
    LabRenderer _labRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const LabEntity& current, const LabEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMLAB_H
