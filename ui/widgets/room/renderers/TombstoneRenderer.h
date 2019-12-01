/*
 * File: TombstoneRenderer.h
 * Created: 2018-12-29
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

#ifndef _TOMBSTONERENDERER_H
#define _TOMBSTONERENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TombstoneRenderer
// Utility class to draw the "Tombstone" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TombstoneRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH               = 75;       // Percentage of cell width
    static const int ENTITY_HEIGHT              = 90;       // Percentage of cell height

    static const int BORDER_PEN_WIDTH           = 2;        // Pixels

    static const int FONT_SIZE_SCALE            = 50;       // Percentage of bounding rect width

public:

    TombstoneRenderer(QObject* parent = nullptr);
    virtual ~TombstoneRenderer();

    void setTotalResources(int totalResources);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

private:
    qreal _totalResources;
};

#endif // _TOMBSTONERENDERER_H
