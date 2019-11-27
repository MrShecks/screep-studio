/*
 * File: ExtractorRenderer.h
 * Created: 2019-1-9
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

#ifndef _EXTRACTORRENDERER_H
#define _EXTRACTORRENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ExtractorRenderer
// Utility class to draw the "Extractor" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ExtractorRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH                       = 140;                  // Percentage of cell width
    static const int ENTITY_HEIGHT                      = ENTITY_WIDTH;

    static constexpr qreal EXTRACTOR_ARC_SIZE_SCALE     = 16;                   // Percentage of bounding rect height
    static constexpr qreal EXTRACTOR_ARC_WIDTH          = 360.0f / 6;           // Degrees

public:

    ExtractorRenderer(QObject* parent = nullptr);
    virtual ~ExtractorRenderer();

    qreal rotation() const;

    void setRotation(qreal rotation);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    //
    // ExtractorRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    qreal _rotation;

    void drawArc(QPainter* painter, const QRectF& rect, qreal startAngle, qreal size) const;
};

#endif // _EXTRACTORRENDERER_H
