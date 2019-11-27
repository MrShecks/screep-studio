/*
 * File: RoomUtils.cpp
 * Created: 2019-1-4
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

#include "RoomUtils.h"
#include "ScreepsApi.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomUtils
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int RoomUtils::getCellIndex(const QPoint& pos) {
    return getCellIndex(pos.x(), pos.y());
}

int RoomUtils::getCellIndex(int x, int y) {
    int index = -1;

    if(x >= 0 && x < Screeps::ROOM_WIDTH && y >= 0 && y < Screeps::ROOM_HEIGHT)
        index = (y * Screeps::ROOM_WIDTH) + x;

    return index;
}

QPoint RoomUtils::getCellPosition(int index) {
    return QPoint(index % Screeps::ROOM_WIDTH, index / Screeps::ROOM_WIDTH);
}

QPoint RoomUtils::getNeighbourPosition(Neighbours neighbour, const QPoint &cellPos) {
    return getNeighbourPosition(neighbour, cellPos.x(), cellPos.y());
}

QPoint RoomUtils::getNeighbourPosition(Neighbours neighbour, int cellX, int cellY) {
    // Note: Must be in the same order as the Neighbours enum
    static const short offsets[Neighbour_Count][2] = {
        {  0, -1 },     // Neighbour_North
        {  1, -1 },     // Neighbour_NorthEast
        {  1,  0 },     // Neighbour_East
        {  1,  1 },     // Neighbour_SouthEast
        {  0,  1 },     // Neighbour_South
        { -1,  1 },     // Neighbour_SouthWest
        { -1,  0 },     // Neighbour_West
        { -1, -1 }      // Neighbour_NorthWest
    };

    return QPoint(cellX + offsets[neighbour][0], cellY + offsets[neighbour][1]);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomUtils::RoomUtils() {

}
