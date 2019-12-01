/*
 * File: RoomGraphicsItemContainer.h
 * Created: 2019-1-6
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

#ifndef ROOMGRAPHICSITEMCONTAINER_H
#define ROOMGRAPHICSITEMCONTAINER_H

#include "RoomGraphicsItem.h"
#include "ui/scenes/room/renderers/ContainerRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ContainerEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ContainerEntity : public StorageRoomEntity {
    typedef StorageRoomEntity _super;

public:
    ContainerEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    int power() const                   { return getStoredResourceAmount(Screeps::ResourceType_POWER); }
    int energy() const                  { return getStoredResourceAmount(Screeps::ResourceType_ENERGY); }

    int energyCapacity() const          { return getInt("energyCapacity"); }

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
// RoomGraphicsItemContainer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemContainer : public TRoomGraphicsItem<ContainerEntity> {
    typedef TRoomGraphicsItem<ContainerEntity> _super;

public:
    RoomGraphicsItemContainer(const ContainerEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemContainer();

private:
    ContainerRenderer _containerRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const ContainerEntity& current, const ContainerEntity& updated) Q_DECL_OVERRIDE;
};

#endif // ROOMGRAPHICSITEMCONTAINER_H
