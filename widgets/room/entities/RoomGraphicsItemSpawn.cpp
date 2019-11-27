/*
 * File: RoomGraphicsItemSpawn.cpp
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

#include <QPainter>

#include "RoomGraphicsItemSpawn.h"
#include "../../../utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SpawnEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SpawnEntity::elapsedSpawnTime() const {
    int elapsedTime = 0;

    if(hasObject("spawning")) {
        const QJsonObject spawning = getObject("spawning");

        elapsedTime = JSONUtils::getInt(spawning, "needTime") - JSONUtils::getInt(spawning, "remainingTime");
    }

    return elapsedTime;
}

int SpawnEntity::totalSpawnTime() const {
    int totalTime = 0;

    if(hasObject("spawning")) {
        const QJsonObject spawning = getObject("spawning");

        totalTime = JSONUtils::getInt(spawning, "needTime");
    }

    return totalTime;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemSpawn
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemSpawn::RoomGraphicsItemSpawn(const SpawnEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_Spawn, entity, cellSize, ItemZOrder_Spawn, parent),
      _spawnRenderer(this) {

    _spawnAnimation.setTargetObject(this);
    _spawnAnimation.setPropertyName("scale");

    _spawnAnimation.setKeyValueAt (0, 1.0);
    _spawnAnimation.setKeyValueAt (0.3, 1.2);
    _spawnAnimation.setKeyValueAt (0.6, 0.8);
    _spawnAnimation.setKeyValueAt (1, 1.0);

    _spawnAnimation.setDuration(SPAWN_ANIMATION_DURATION);
    _spawnAnimation.setLoopCount(-1);

    //_spawnAnimation.start();

    setToolTip(itemEntity().getString("name"));
    setTransformOriginPoint(boundingRect().center());       // FIXME: Do we still need this? (Might be needed for the scale animation)

    _spawnRenderer.setEnergy(entity.energy());
    _spawnRenderer.setEnergyCapacity(entity.energyCapacity());
    _spawnRenderer.setSpawnProgress(entity.elapsedSpawnTime(), entity.totalSpawnTime());
}

RoomGraphicsItemSpawn::~RoomGraphicsItemSpawn() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemSpawn::itemSize(const QSize& cellSize) const {
    return _spawnRenderer.size(cellSize);
}

void RoomGraphicsItemSpawn::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _spawnRenderer.draw (painter, bounds);

    Q_UNUSED(option);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool RoomGraphicsItemSpawn::beginUpdate(const SpawnEntity& current, const SpawnEntity& updated) {
    const SpawnEntity::State currentState = current.state();
    const SpawnEntity::State updatedState = updated.state();

    if(current.energy() != updated.energy())
        _spawnRenderer.setEnergy(updated.energy());

    if(current.energyCapacity() != updated.energyCapacity())
        _spawnRenderer.setEnergyCapacity(updated.energyCapacity());

    // If the state has just changed from spawning to idle then
    // we need to hide the spawn progress indicator

    if(currentState != updatedState && updatedState == SpawnEntity::State_Idle) {
        _spawnRenderer.setSpawnProgress(0, 0);
    }

    if(updatedState == SpawnEntity::State_Spawning)
        _spawnRenderer.setSpawnProgress(updated.elapsedSpawnTime(), updated.totalSpawnTime());

    return _spawnRenderer.isDirty();
}
