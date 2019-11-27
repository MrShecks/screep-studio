/*
 * File: RoomGraphicsItemStorage.cpp
 * Created: 2019-1-2
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

#include <QPainter>

#include "ScreepsApi.h"
#include "RoomGraphicsItemStorage.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemStorage
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemStorage::RoomGraphicsItemStorage(const StorageEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Storage, entity, cellSize, ItemZOrder_Storage, parent),
      _storageRenderer(this),
      _glow(this) {

    _glow.setScale(GLOW_EFFECT_SCALE);
    _glow.setOpacity(GLOW_EFFECT_OPACITY);

    const int totalResources = entity.getTotalResources();

    _storageRenderer.setPower(entity.power());
    _storageRenderer.setEnergy(entity.energy());
    _storageRenderer.setTotalResources(totalResources);
    _storageRenderer.setResourceCapacity(entity.energyCapacity());

    _glow.setVisible (totalResources > 0);
}

RoomGraphicsItemStorage::~RoomGraphicsItemStorage() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemStorage::itemSize(const QSize& cellSize) const {
    return _storageRenderer.size(cellSize);
}

void RoomGraphicsItemStorage::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _storageRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemStorage::beginUpdate(const StorageEntity& current, const StorageEntity& updated) {

    if(current.energy() != updated.energy())
        _storageRenderer.setEnergy(updated.energy());

    if(current.power()!= updated.power())
        _storageRenderer.setPower(updated.power());

    const int currentTotalResources = current.getTotalResources();
    const int updatedTotalResources = updated.getTotalResources();

    if(currentTotalResources != updatedTotalResources)
        _storageRenderer.setTotalResources(updatedTotalResources);

    if(current.energyCapacity()!= updated.energyCapacity())
        _storageRenderer.setResourceCapacity(updated.energyCapacity());

    if(_storageRenderer.isDirty())
        _glow.setVisible(updatedTotalResources > 0);

    return _storageRenderer.isDirty();
}

//{
//    "_id": "5c2bdda650794c04267d4afb",
//    "energy": 115870,
//    "energyCapacity": 1000000,
//    "hits": 10000,
//    "hitsMax": 10000,
//    "notifyWhenAttacked": true,
//    "room": "W8N3",
//    "type": "storage",
//    "user": "5c219cbd6edd010419f53a3a",
//    "x": 29,
//    "y": 10
//}

//{
//    "G": 0,
//    "GH": 2290,
//    "GH2O": 0,
//    "GHO2": 0,
//    "GO": 95,
//    "H": 2900,
//    "K": 0,
//    "KH": 0,
//    "KH2O": 0,
//    "KHO2": 17,
//    "KO": 8702,
//    "L": 14420,
//    "LH": 2471,
//    "LH2O": 0,
//    "LHO2": 0,
//    "LO": 0,
//    "O": 0,
//    "OH": 0,
//    "U": 0,
//    "UH": 11,
//    "UH2O": 0,
//    "UHO2": 0,
//    "UL": 0,
//    "UO": 0,
//    "X": 0,
//    "XGH2O": 4525,
//    "XGHO2": 2399,
//    "XKH2O": 0,
//    "XKHO2": 3528,
//    "XLH2O": 917,
//    "XLHO2": 3147,
//    "XUH2O": 4088,
//    "XUHO2": 0,
//    "XZH2O": 5200,
//    "XZHO2": 4354,
//    "Z": 0,
//    "ZH": 0,
//    "ZH2O": 0,
//    "ZHO2": 0,
//    "ZK": 0,
//    "ZO": 0,
//    "_id": "5bad32b09dca93647d1bb261",
//    "energy": 237491,
//    "energyCapacity": 1000000,
//    "hits": 10000,
//    "hitsMax": 10000,
//    "notifyWhenAttacked": true,
//    "power": 0,
//    "room": "W19S47",
//    "type": "storage",
//    "user": "5b1d1c9e340d195a66436301",
//    "x": 27,
//    "y": 34
//}
