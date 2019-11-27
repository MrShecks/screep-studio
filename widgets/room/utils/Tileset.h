/*
 * File: Tileset.h
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

#ifndef _TILESET_H
#define _TILESET_H

#include <QString>
#include <QPixmap>
#include <QPainter>
#include <QHash>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Tileset
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Tileset {

public:
    Tileset(const QString& fileName, int tileWidth, int tileHeight);
    virtual ~Tileset();

    int tileWidth() const                       { return _tileWidth; }
    int tileHeight() const                      { return _tileHeight; }

    bool drawTile(QPainter* painter, int index, const QRectF& rect) const;
    bool drawMappedTile(QPainter* painter, int tileId, const QRectF& rect) const;

    void addMapping(int tileId, int index);

private:
    typedef QHash<int, int> TIndexMap;

    int _tileWidth;
    int _tileHeight;

    int _rowCount;
    int _columnCount;

    QPixmap _image;

    TIndexMap _indexMap;
};

#endif // _TILESET_H
