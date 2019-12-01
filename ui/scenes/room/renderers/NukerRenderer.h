/*
 * File: NukerRenderer.h
 * Created: 2019-1-23
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

#ifndef _NUKERRENDERER_H
#define _NUKERRENDERER_H

#include <QPainterPath>

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NukerRenderer
// Utility class to draw the "Nuker" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NukerRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH                       = 140;      // Percentage of cell width
    static const int ENTITY_HEIGHT                      = 200;      // Percentage of cell height

    static const int BORDER_PEN_WIDTH_SCALE             = 4;        // Percentage of bounding rect width

    static const int ENERGY_STORE_PADDING_SCALE         = 4;        // Percentage of bounding rect width

    static const int RESOURCE_STORE_HEIGHT_SCALE        = 18;       // Percentage of bounding rect height

    static const int RESROUCE_STORE_BAR_HEIGHT_SCALE    = RESOURCE_STORE_HEIGHT_SCALE - 6;

public:

    NukerRenderer(QObject* parent = nullptr);
    virtual ~NukerRenderer();

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    void setEnergy(int energy);
    void setResources(int resource);

    void setEnergyCapacity(int energyCapacity);
    void setResourceCapacity(int resourceCapacity);

    //
    // LabRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    qreal _energy;
    qreal _resources;

    qreal _energyCapacity;
    qreal _resourceCapacity;

    QPainterPath basePath(const QRectF& rect) const;
    QPainterPath energyStorePath(const QRectF& rect) const;

    QRectF resourceStoreRect(const QRectF& rect) const;
};

#endif // _NUKERRENDERER_H
