/*
 * File: LabRenderer.h
 * Created: 2019-1-22
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

#ifndef _LABRENDERER_H
#define _LABRENDERER_H

#include <QPainterPath>

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LabRenderer
// Utility class to draw the "Lab" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LabRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH                       = 90;       // Percentage of cell width
    static const int ENTITY_HEIGHT                      = 90;       // Percentage of cell height

    static const int BORDER_PEN_WIDTH_SCALE             = 4;        // Percentage of bounding rect width

    static const int RESOURCE_STORE_SIZE_SCALE          = 80;       // Percentage of bounding rect
    static const int ENERGY_STORE_SIZE_SCALE            = 75;       // Percentage of bounding rect

    static const int ENERGY_BAR_HEIGHT_SCALE            = 14;       // Percentage of bounding rect height

public:

    LabRenderer(QObject* parent = nullptr);
    virtual ~LabRenderer();

    void setEnergy(int energy);
    void setEnergyCapacity(int energyCapacity);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    //
    // LabRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    qreal _energy;
    qreal _energyCapacity;

    QPainterPath basePath(const QRectF& rect) const;
    QRectF energyStoreRect(const QRectF& rect, qreal borderPenWidth) const;
};

#endif // _LABRENDERER_H
