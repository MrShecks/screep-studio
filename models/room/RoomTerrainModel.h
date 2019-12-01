/*
 * File: RoomTerrain.h
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

#ifndef _ROOMTERRAINMODEL_H
#define _ROOMTERRAINMODEL_H

#include <QString>
#include <QList>

#include "ScreepsApi.h"
#include "RoomUtils.h"
#include "network/rest/RestRoomTerrain.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomModel()
// Representation of the the fixed terrain for a world room. E.g Plain areas, fixed walls, swamps etc.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomTerrainModel : public QObject {
    typedef QObject _super;

    Q_OBJECT

    friend class RoomModel;

public:
    static const int ROOM_WIDTH                 = Screeps::ROOM_WIDTH;
    static const int ROOM_HEIGHT                = Screeps::ROOM_HEIGHT;

    // Each cell will be represented as a 16 unsigned (quint16) integer as follows
    //
    // +--------+---------+
    // | A      | B       |
    // +--------+---------+
    //
    // Where:-
    // A (8 bits) is the tiles tileset index which will be a bitmap of RoomUtils::NeighbourFlags
    // B (8 bits) is the tiles terrain type bitmap (Screeps::TerrainFlags)

    RoomTerrainModel(QObject* parent = nullptr);
    virtual ~RoomTerrainModel();

    int height() const                  { return ROOM_HEIGHT; }
    int width() const                   { return ROOM_WIDTH; }

    bool isEmpty() const                { return _isEmpty; }

    Screeps::TerrainFlags getTerrainType(int x, int y, Screeps::TerrainFlags defaultFlags = Screeps::TerrainFlag_None) const;
    RoomUtils::NeighbourFlags getNeighbourFlags(int x, int y) const;

signals:
    void terrainUpdated(const RoomTerrainModel& terrainModel);

private:
    static const quint16 TERRAIN_TYPE_MASK      = 0x00FF;
    static const quint16 TERRAIN_FLAG_MASK      = 0xFF00;
    static const int TERRAIN_FLAG_SHIFT         = 8;

    typedef quint16 TTerrainCell;
    static const TTerrainCell TERRAINCELL_INVALID = static_cast<TTerrainCell>(-1);

    bool _isEmpty;
    TTerrainCell _cells[ROOM_WIDTH * ROOM_HEIGHT];

    void setTerrain(const RestResponseRoomTerrain::Room& room);

    RoomUtils::NeighbourFlags getNeighbourFlags(int x, int y, Screeps::TerrainFlags allowedNeighbours, const RestResponseRoomTerrain::Room& room) const;

    TTerrainCell getCell(int x, int y) const;
};

#endif // _ROOMTERRAINMODEL_H
