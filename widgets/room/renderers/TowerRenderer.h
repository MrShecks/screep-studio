/*
 * File: TowerRenderer.h
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

#ifndef _TOWERRENDERER_H
#define _TOWERRENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TowerRenderer
// Utility class to draw the "Tower" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TowerRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH               = 160;      // Percentage of cell width
    static const int ENTITY_HEIGHT              = 160;      // Percentage of cell height

    static const int BORDER_PEN_WIDTH           = 3;        // Pixels

    static const int TOWER_BASE_SIZE            = 70;       // Percentage of bounding rect

    static const int ENERGY_STORE_WIDTH         = 50;       // Percentage of bounding rect width
    static const int ENERGY_STORE_HEIGHT        = 32;       // Percentage of bounding rect height

    static const int TURRET_WIDTH               = 25;       // Percentage of bounding rect width
    static const int TURRET_HEIGHT              = 30;       // Percentage of bounding rect height

public:

    TowerRenderer(QObject* parent = nullptr);
    virtual ~TowerRenderer();

    qreal rotation() const;

    void setRotation(qreal rotation);
    void setEnergy(int energy);
    void setEnergyCapacity(int energyCapacity);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    //
    // TowerRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    qreal _rotation;

    qreal _energy;
    qreal _energyCapacity;
};

#endif // _TOWERRENDERER_H
