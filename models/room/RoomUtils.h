/*
 * File: RoomUtils.h
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

#ifndef _ROOMUTILS_H
#define _ROOMUTILS_H

#include <QFlags>
#include <QPoint>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomUtils
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomUtils {
public:

    //
    // Note: Order of the Neighbours and NeighbourFlag enums are important.
    // If they are re-ordered code will break unless updated. See RoomTerrainModel
    // and RoomEntityModel.
    //

    enum Neighbours {
        Neighbour_North                         = 0,
        Neighbour_NorthEast                     = 1,
        Neighbour_East                          = 2,
        Neighbour_SouthEast                     = 3,
        Neighbour_South                         = 4,
        Neighbour_SouthWest                     = 5,
        Neighbour_West                          = 6,
        Neighbour_NorthWest                     = 7,

        Neighbour_Count
    };

    enum NeighbourFlag {
        NeighbourFlag_None                      = 0,

        NeighbourFlag_North                     = 1 << Neighbour_North,
        NeighbourFlag_NorthEast                 = 1 << Neighbour_NorthEast,
        NeighbourFlag_East                      = 1 << Neighbour_East,
        NeighbourFlag_SouthEast                 = 1 << Neighbour_SouthEast,
        NeighbourFlag_South                     = 1 << Neighbour_South,
        NeighbourFlag_SouthWest                 = 1 << Neighbour_SouthWest,
        NeighbourFlag_West                      = 1 << Neighbour_West,
        NeighbourFlag_NorthWest                 = 1 << Neighbour_NorthWest,

        NeighbourFlag_All                       = 0xFF
    };

    Q_DECLARE_FLAGS(NeighbourFlags, NeighbourFlag)

    static int getCellIndex(const QPoint& pos);
    static int getCellIndex(int x, int y);

    static QPoint getCellPosition(int index);

    static QPoint getNeighbourPosition(Neighbours neighbour, const QPoint& cellPos);
    static QPoint getNeighbourPosition(Neighbours neighbour, int cellX, int cellY);

private:
    RoomUtils();
};

Q_DECLARE_OPERATORS_FOR_FLAGS(RoomUtils::NeighbourFlags);

#endif // _ROOMUTILS_H
