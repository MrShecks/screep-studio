/*
 * File: ConstructionSiteRenderer.h
 * Created: 2019-1-1
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

#ifndef _CONSTRUCTIONSITERENDERER_H
#define _CONSTRUCTIONSITERENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConstructionSiteRenderer
// Utility class to draw a the "construction site" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ConstructionSiteRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH                   = 60;       // Percentage of cell width
    static const int ENTITY_HEIGHT                  = 60;       // Percentage of cell height

    static const int BORDER_PEN_WIDTH               = 6;        // Pixels

public:

    ConstructionSiteRenderer(QObject* parent = nullptr);
    virtual ~ConstructionSiteRenderer();

    void setProgress(int progress, int progressTotal);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

private:
    qreal _progress;
    qreal _progressTotal;
};

#endif // _CONSTRUCTIONSITERENDERER_H
