/*
 * File: ControllerRenderer.h
 * Created: 2019-1-5
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

#ifndef _CONTROLLERRENDERER_H
#define _CONTROLLERRENDERER_H

#include <QPainterPath>

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ControllerRenderer
// Utility class to draw the "Room Controller" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ControllerRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH                       = 140;      // Percentage of cell width
    static const int ENTITY_HEIGHT                      = 140;      // Percentage of cell height

    static const int BORDER_PEN_WIDTH                   = 4;        // Pixels
    static const int SEGMENT_PEN_WIDTH                  = 8;        // Pixels
    static const int SEGMENT_SPACING                    = 4;        // Pixels

    static const int PROGRESS_SIZE_SCALE                = 65;       // Percentage of bounding rect

    static const int PEN_WIDTH                          = 6;

    static const int CONTROLLER_WIDTH_SCALE             = 140;      // Percentage of cell width
    static const int CONTROLLER_HEIGHT_SCALE            = 140;      // Percentage of cell width
    static const int CONTROLLER_SEGMENT_HEIGHT_SCALE    = 12;       // Percentage of cell height

    static const int CONTROLLER_LEVEL_SEGMENT_SPACING   = 4;

public:

    ControllerRenderer(QObject* parent = nullptr);
    virtual ~ControllerRenderer();

    void setLevel(int controllerLevel);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

private:
    int _controllerLevel;
};

#endif // _CONTROLLERRENDERER_H
