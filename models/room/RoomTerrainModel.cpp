/*
 * File: RoomTerrain.cpp
 * Created: 2018-11-24
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

#include "RoomTerrainModel.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif // QT_DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomModel()
// Representation of the the fixed terrain for a world room. E.g Plain areas, fixed walls, swamps etc.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomTerrainModel::RoomTerrainModel(QObject* parent /* = nullptr */)
    : _super(parent),
      _isEmpty(true),
      _cells() {

}

RoomTerrainModel::~RoomTerrainModel() {

}

Screeps::TerrainFlags RoomTerrainModel::getTerrainType(int x, int y, Screeps::TerrainFlags defaultFlags /* = Screeps::TerrainFlag_None */) const {
    Screeps::TerrainFlags terrainFlags = defaultFlags;
    TTerrainCell terrainCell;

    if((terrainCell = getCell(x, y)) != TERRAINCELL_INVALID)
        terrainFlags = static_cast<Screeps::TerrainFlags>(terrainCell & TERRAIN_TYPE_MASK);

    return terrainFlags;
}

RoomUtils::NeighbourFlags RoomTerrainModel::getNeighbourFlags(int x, int y) const {
    RoomUtils::NeighbourFlags flags = RoomUtils::NeighbourFlag_None;
    TTerrainCell terrainCell;

    if((terrainCell = getCell(x, y)) != TERRAINCELL_INVALID)
        flags = static_cast<RoomUtils::NeighbourFlags>((terrainCell & TERRAIN_FLAG_MASK) >> TERRAIN_FLAG_SHIFT);

    return flags;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomTerrainModel::setTerrain(const RestResponseRoomTerrain::Room& room) {

    for(int x = 0; x < room.width(); ++x) {
        for(int y = 0; y< room.height(); ++y) {
            Screeps::TerrainFlags terrainTypeFlags = room.getCell(x, y);
            Screeps::TerrainFlags allowedNeighbours = Screeps::TerrainFlag_None;

            switch(terrainTypeFlags) {
                case Screeps::TerrainFlag_Plain:        allowedNeighbours = Screeps::TerrainFlag_Plain;         break;
                case Screeps::TerrainFlag_Wall:         allowedNeighbours = Screeps::TerrainFlag_SwampyWall;    break;
                case Screeps::TerrainFlag_Swamp:        allowedNeighbours = Screeps::TerrainFlag_SwampyWall;    break;
                case Screeps::TerrainFlag_SwampyWall:   allowedNeighbours = Screeps::TerrainFlag_Wall;          break;
            }

            RoomUtils::NeighbourFlags flags = getNeighbourFlags(x, y, allowedNeighbours, room);

            _cells[(y * room.width ()) + x] = (flags << 8) | terrainTypeFlags;
        }
    }

    _isEmpty = false;
    emit terrainUpdated(*this);
}

RoomUtils::NeighbourFlags RoomTerrainModel::getNeighbourFlags(int x, int y, Screeps::TerrainFlags allowedNeighbours, const RestResponseRoomTerrain::Room& room) const {
    RoomUtils::NeighbourFlags flags = RoomUtils::NeighbourFlag_None;

    for(int n = 0; n < RoomUtils::Neighbour_Count; ++n) {
        const QPoint pos = RoomUtils::getNeighbourPosition(static_cast<RoomUtils::Neighbours>(n), x, y);
        const Screeps::TerrainFlags neighbourTypeFlags = room.getCell(pos.x(), pos.y(), Screeps::TerrainFlag_None);

        if(neighbourTypeFlags == Screeps::TerrainFlag_None || (neighbourTypeFlags & allowedNeighbours) != 0)
            flags |= static_cast<RoomUtils::NeighbourFlag>(1 << n);
    }

    //
    // Remove corner combinations that will result in duplicate tile indexes
    //

    if((flags & RoomUtils::NeighbourFlag_NorthEast) != 0 && ((flags & RoomUtils::NeighbourFlag_North) == 0 || (flags & RoomUtils::NeighbourFlag_East) == 0))
        flags &= ~RoomUtils::NeighbourFlag_NorthEast;

    if((flags & RoomUtils::NeighbourFlag_SouthEast) != 0 && ((flags & RoomUtils::NeighbourFlag_South) == 0 || (flags & RoomUtils::NeighbourFlag_East) == 0))
        flags &= ~RoomUtils::NeighbourFlag_SouthEast;

    if((flags & RoomUtils::NeighbourFlag_SouthWest) != 0 && ((flags & RoomUtils::NeighbourFlag_South) == 0 || (flags & RoomUtils::NeighbourFlag_West) == 0))
        flags &= ~RoomUtils::NeighbourFlag_SouthWest;

    if((flags & RoomUtils::NeighbourFlag_NorthWest) != 0 && ((flags & RoomUtils::NeighbourFlag_North) == 0 || (flags & RoomUtils::NeighbourFlag_West) == 0))
        flags &= ~RoomUtils::NeighbourFlag_NorthWest;

    return flags;
}

RoomTerrainModel::TTerrainCell RoomTerrainModel::getCell(int x, int y) const {
    TTerrainCell terrainCell = TERRAINCELL_INVALID;

    if(x >= 0 && x < ROOM_WIDTH && y >= 0 && y < ROOM_HEIGHT)
        terrainCell = _cells[(y * ROOM_WIDTH) + x];

    return terrainCell;
}
