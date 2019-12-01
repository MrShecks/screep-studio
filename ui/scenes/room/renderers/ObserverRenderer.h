/*
 * File: ObserverRenderer.h
 * Created: 2019-2-1
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

#ifndef _OBSERVERRENDERER_H
#define _OBSERVERRENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ObserverRenderer
// Utility class to draw the "Observer" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ObserverRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH               = 90;       // Percentage of cell width
    static const int ENTITY_HEIGHT              = 90;       // Percentage of cell height

    static const int BASE_WIDTH_SCALE           = 100;      // Percentage of bounding rect width
    static const int BASE_HEIGHT_SCALE          = 90;       // Percentage of bounding rect height

    static const int BORDER_PEN_SCALE           = 6;        // Percentage of bounding rect width
    static const int EYE_RADIUS_SCALE           = 20;       // Percentage of bounding rect width

public:

    ObserverRenderer(QObject* parent = nullptr);
    virtual ~ObserverRenderer();

    qreal eyeRotation() const;
    void setEyeRotation(qreal eyeRotation);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    //
    // ObserverRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    qreal _eyeRotation;
};

#endif // _OBSERVERRENDERER_H
