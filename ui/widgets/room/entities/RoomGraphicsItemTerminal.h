/*
 * File: RoomGraphicsItemTerminal.h
 * Created: 2019-1-18
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

#ifndef _ROOMGRAPHICSITEMTERMINAL_H
#define _ROOMGRAPHICSITEMTERMINAL_H

#include "RoomGraphicsItem.h"
#include "GraphicsItemGlow.h"
#include "../renderers/TerminalRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TerminalEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TerminalEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:
    TerminalEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    int power() const                   { return getStoredResourceAmount(Screeps::ResourceType_POWER); }
    int energy() const                  { return getStoredResourceAmount(Screeps::ResourceType_ENERGY); }

    int energyCapacity() const          { return getStoreCapacity(); }

    int getStoredResourceAmount(Screeps::ResourceType type) const {
        return _super::getStoredResourceAmount(Screeps::RESOURCES_ALL[type]);
    }

    int getTotalResources() const {
        int totalResources = 0;

        for(const QString& resourceName : Screeps::RESOURCES_ALL)
            totalResources += _super::getStoredResourceAmount(resourceName);

        return totalResources;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemTerminal
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemTerminal : public TRoomGraphicsItem<TerminalEntity> {
    typedef TRoomGraphicsItem<TerminalEntity> _super;

    static constexpr qreal GLOW_EFFECT_SCALE    = 2.0;
    static constexpr qreal GLOW_EFFECT_OPACITY  = 0.5;

public:
    RoomGraphicsItemTerminal(const TerminalEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemTerminal();

private:
    TerminalRenderer _terminalRenderer;
    GraphicsItemGlow _glow;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const TerminalEntity& current, const TerminalEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMTERMINAL_H
