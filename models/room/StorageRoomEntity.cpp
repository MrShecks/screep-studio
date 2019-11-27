/*
 * File: StorageRoomEntity.cpp
 * Created: 2019-11-27
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

#include "StorageRoomEntity.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StorageRoomEntity
// Base utility class for entities that have "store" and "storeCapacityResource" components
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StorageRoomEntity::~StorageRoomEntity() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StorageRoomEntity::StorageRoomEntity(const RoomEntity& entity)
    : _super(entity) {

}
