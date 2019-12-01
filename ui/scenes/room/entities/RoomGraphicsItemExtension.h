/*
 * File: RoomGraphicsItemExtension.h
 * Created: 2018-12-12
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

#ifndef _ROOMGRAPHICSITEMEXTENSION_H
#define _ROOMGRAPHICSITEMEXTENSION_H

#include <QPropertyAnimation>

#include "RoomGraphicsItem.h"
#include "GraphicsItemGlow.h"
#include "ui/scenes/room/renderers/ExtensionRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ExtensionEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ExtensionEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:
    ExtensionEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    int energy() const                  { return getStoredResourceAmount("energy"); }
    int energyCapacity() const          { return getStoredResourceCapacity("energy"); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemExtension
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemExtension : public TRoomGraphicsItem<ExtensionEntity> {
    typedef TRoomGraphicsItem<ExtensionEntity> _super;

    static constexpr qreal GLOW_EFFECT_SCALE    = 1.3;
    static constexpr qreal GLOW_EFFECT_OPACITY  = 0.2;

public:
    RoomGraphicsItemExtension(const ExtensionEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemExtension();

private:
    ExtensionRenderer _extensionRenderer;
    GraphicsItemGlow _glow;

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const ExtensionEntity& current, const ExtensionEntity& updated) Q_DECL_OVERRIDE;
};

//"61fd98d5fcc0e8b": {
//      "$loki": 3292,
//      "_id": "61fd98d5fcc0e8b",
//      "energy": 50,
//      "energyCapacity": 50,
//      "hits": 1000,
//      "hitsMax": 1000,
//      "meta": {
//        "created": 1544469438412,
//        "revision": 51,
//        "updated": 1544578854158,
//        "version": 0
//      },
//      "notifyWhenAttacked": true,
//      "off": false,
//      "room": "W8N3",
//      "type": "extension",
//      "user": "c2b3bdb9a49482e",
//      "x": 8,
//      "y": 9
//    },
#endif // _ROOMGRAPHICSITEMEXTENSION_H
