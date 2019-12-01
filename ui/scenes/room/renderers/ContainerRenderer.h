/*
 * File: ContainerRenderer.h
 * Created: 2019-1-6
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

#ifndef _CONTAINERRENDERER_H
#define _CONTAINERRENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ContainerRenderer
// Utility class to draw the "Container" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ContainerRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH               = 55;       // Percentage of cell width
    static const int ENTITY_HEIGHT              = 70;       // Percentage of cell height

    static const int BORDER_PEN_WIDTH           = 4;        // Pixels

    static const int ENERGY_STORE_SIZE          = 90;       // Percentage of bounding rect

public:

    ContainerRenderer(QObject* parent = nullptr);
    virtual ~ContainerRenderer();

    void setEnergy(int energy);
    void setPower(int power);

    void setTotalResources(int totalResources);

    void setResourceCapacity(int resourceCapacity);


    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    //
    // ContainerRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    qreal _energy;
    qreal _power;

    qreal _totalResources;

    qreal _resourceCapacity;

    void drawResourceBar(QPainter* painter, const QRectF& rect, qreal resources, const QColor& color) const;
};

#endif // _CONTAINERRENDERER_H
