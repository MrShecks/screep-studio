/*
 * File: RoomGraphicsItem.h
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

#ifndef _ROOMGRAPHICSITEM_H
#define _ROOMGRAPHICSITEM_H

#include <QGraphicsObject>

#include "ScreepsApi.h"
#include "GraphicsItemSelection.h"
#include "models/room/RoomEntity.h"
#include "models/room/StorageRoomEntity.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItem
// Base class for room graphics items use to visually represent room entities
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItem : public QGraphicsObject {
    typedef QGraphicsObject _super;

    friend class RoomGraphicsScene;

    static constexpr qreal SELECTION_PEN_WIDTH  = 6;
    static constexpr qreal SELECTION_PADDING    = 6;

    static const QColor SELECTION_PEN_COLOR;

public:

    enum GraphicsItemType {
        ItemType_Unknown                        = UserType,

        ItemType_Wall                           = UserType + Screeps::EntityType_Wall,
        ItemType_Creep                          = UserType + Screeps::EntityType_Creep,
        ItemType_Spawn                          = UserType + Screeps::EntityType_Spawn,
        ItemType_Tower                          = UserType + Screeps::EntityType_Tower,
        ItemType_Source                         = UserType + Screeps::EntityType_Source,
        ItemType_Mineral                        = UserType + Screeps::EntityType_Mineral,
        ItemType_Extractor                      = UserType + Screeps::EntityType_Extractor,
        ItemType_Extension                      = UserType + Screeps::EntityType_Extension,
        ItemType_Controller                     = UserType + Screeps::EntityType_Controller,
        ItemType_ConstructionSite               = UserType + Screeps::EntityType_ConstructionSite,
        ItemType_Tombstone                      = UserType + Screeps::EntityType_Tombstone,
        ItemType_Storage                        = UserType + Screeps::EntityType_Storage,
        ItemType_Container                      = UserType + Screeps::EntityType_Container,
        ItemType_Road                           = UserType + Screeps::EntityType_Road,
        ItemType_Link                           = UserType + Screeps::EntityType_Link,
        ItemType_Energy                         = UserType + Screeps::EntityType_Energy,
        ItemType_Terminal                       = UserType + Screeps::EntityType_Terminal,
        ItemType_Lab                            = UserType + Screeps::EntityType_Lab,
        ItemType_Nuker                          = UserType + Screeps::EntityType_Nuker,
        ItemType_Rampart                        = UserType + Screeps::EntityType_Rampart,
        ItemType_PowerSpawn                     = UserType + Screeps::EntityType_PowerSpawn,
        ItemType_Observer                       = UserType + Screeps::EntityType_Observer
    };

    //
    // Item Z-orders from the opensource Screeps room renderer code.
    //
    // ItemZOrder_Road = -1
    // ItemZOrder_Rampart = 0
    // ItemZOrder_Extractor = 0
    // ItemZOrder_Wall = 0
    // ItemZOrder_Energy = 1,
    // ItemZOrder_Source = 2,
    // ItemZOrder_Mineral = 2,
    // ItemZOrder_Container = 4
    // ItemZOrder_Controller = 4
    // ItenZOrder_Tombstone = 5
    // ItemZOrder_Creep = 6
    // ItemZOrder_Extension = 7
    // ItemZOrder_Storage = 7
    // ItemZOrder_Nuker = 7
    // ItemZOrder_Spawn = 8
    // ItemZOrder_Link = 9
    // ItemZOrder_Observer = 10
    // ItemZOrder_PowerSpwan = 12
    // ItemZOrder_Tower = 13
    // ItemZOrder_Lab = 15
    // ITemZOrder_Terminal = 16
    // ItemZOrder_ConstructionSite = 18
    //

    enum GraphicsItemZOrder {
        ItemZOrder_Background                   = -1,
        ItemZOrder_Road,
        ItemZOrder_Wall,
        ItemZOrder_Rampart,
        ItemZOrder_Extractor,
        ItemZOrder_Energy,
        ItemZOrder_Source,
        ItemZOrder_Mineral,
        ItemZOrder_Container,
        ItemZOrder_Controller,
        ItemZOrder_Tombstone,
        ItemZOrder_Creep,
        ItemZOrder_Extension,
        ItemZOrder_Storage,
        ItemZOrder_Nuker,
        ItemZOrder_Spawn,
        ItemZOrder_Link,
        ItemZOrder_Observer,
        ItemZOrder_PowerSpawn,
        ItemZOrder_Tower,
        ItemZOrder_Lab,
        ItemZOrder_Terminal,
        ItemZOrder_ConstructionSite,

        ItemZOrder_EnergyBeam,

        ItemZOrder_Default                      = ItemZOrder_Background
    };

    virtual ~RoomGraphicsItem();

    virtual const RoomEntity& roomEntity() const = 0;

    static RoomGraphicsItem* create(const QString& type, const RoomEntity& entity, const QSize& cellSize);

    //
    // QGraphicsItem
    //

    int type() const Q_DECL_OVERRIDE;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;

protected:
    RoomGraphicsItem(GraphicsItemType type, const QSize& cellSize, GraphicsItemZOrder zOrder = ItemZOrder_Default, QGraphicsItem* parent = nullptr);

    void setPosition(int roomX, int roomY);
    void setPosition(const QPoint& roomPos);

    QPoint roomToScene(int roomX, int roomY) const;
    QPoint roomToScene(const QPoint& roomPos) const;

    QPoint sceneToRoom(const QPointF& point) const;

    QPoint centerPoint(int roomX, int roomY) const;
    QPoint centerPoint(const QPoint& roomPos) const;

    qreal angleToRoomTarget(const QPoint& roomPos) const;
    qreal angleToSceneTarget(const QPoint& scenePos) const;

    QRectF itemRect() const;

    virtual void applyUpdate(const RoomEntity& entity, int gameTime) = 0;

    virtual QSizeF itemSize(const QSize& cellSize) const = 0;
    virtual void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& rect) = 0;

private:
    GraphicsItemType _type;
    QSize _cellSize;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRoomGraphicsItem
// Utilitiy template class used as a convenience for RoomGraphicsItem subclasses so that they can work
// with entity specific data types rather than the RoomEntity base class.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class TRoomGraphicsItem : public RoomGraphicsItem {
    typedef RoomGraphicsItem _super;

public:
    virtual ~TRoomGraphicsItem() {

    }

    const RoomEntity& roomEntity() const Q_DECL_OVERRIDE {
        return itemEntity();
    }

protected:
    TRoomGraphicsItem(GraphicsItemType type, const T& entity, const QSize& cellSize, GraphicsItemZOrder zOrder = ItemZOrder_Default, QGraphicsItem* parent = nullptr)
        : _super(type, cellSize, zOrder, parent),
          _entity(entity) {

        setPosition(entity.posX(), entity.posY());

#ifdef QT_DEBUG
        setToolTip(QString("Type:\t%1\nId:\t%2").arg(entity.type()).arg(entity.id()));
#endif // QT_DEBUG
    }

    const T& itemEntity() const {
        return _entity;
    }

    void applyUpdate(const RoomEntity& entity, int gameTime) Q_DECL_OVERRIDE  {
        bool shouldUpdate = beginUpdate(_entity, entity);

        _entity = entity;

        if(shouldUpdate)
            update();

        endUpdate(_entity);

        // FIXME: Might remove this and use the game tick from the CPU channel instead
        Q_UNUSED(gameTime);
    }

private:
    T _entity;

    virtual bool beginUpdate(const T& current, const T& updated) {
        Q_UNUSED(current);
        Q_UNUSED(updated);

        return false;
    }

    virtual void endUpdate(const T& current) {
        Q_UNUSED(current);
    }
};

#endif // _ROOMGRAPHICSITEM_H

