/*
 * File: Tileset.cpp
 * Created: 2018-12-22
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

#include "Tileset.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tileset
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Tileset::Tileset(const QString& fileName, int tileWidth, int tileHeight)
    : _tileWidth(tileWidth),
      _tileHeight(tileHeight),
      _image(fileName) {

    _rowCount = _image.height() / tileHeight;
    _columnCount = _image.width() / tileHeight;
}

Tileset::~Tileset() {

}

bool Tileset::drawTile(QPainter* painter, int index, const QRectF& rect) const {
    bool result = false;

    if(index >= 0 && index < (_rowCount * _columnCount)) {
        const int x = index % _columnCount;
        const int y = index / _columnCount;
        const QRectF src = QRectF(x * _tileWidth, y * _tileHeight, _tileWidth, _tileHeight);

        painter->drawPixmap(rect, _image, src);
        result = true;
    }

    return result;
}

bool Tileset::drawMappedTile(QPainter* painter, int tileId, const QRectF& rect) const {
    bool result = false;
    int index;

    if((index = _indexMap.value(tileId, -1)) != -1)
        result = drawTile(painter, index, rect);

    return result;
}

void Tileset::addMapping(int tileId, int index) {
    _indexMap.insert(tileId, index);
}
