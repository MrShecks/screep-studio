/*
 * File: TerrainTileset.cpp
 * Created: 2018-12-23
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

#include "TerrainTileset.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TerrainTileset
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TerrainTileset::TerrainTileset(const QString& fileName, int tileWidth, int tileHeight)
    : _super(fileName, tileWidth, tileHeight) {

//    addMapping (  7, 44);
//    addMapping ( 28,  4);
//    addMapping ( 31, 27);
//    addMapping (112,  3);
//    addMapping (124,  5);
//    addMapping (127, 12);
//    addMapping (193, 43);
//    addMapping (199, 45);
//    addMapping (241, 38);
//    addMapping (247, 20);
//    addMapping (253, 28);
//    addMapping (255, 13 /*37*/);
}

TerrainTileset::~TerrainTileset() {

}
