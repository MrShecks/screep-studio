/*
 * File: PowerSpawnRenderer.h
 * Created: 2019-1-31
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

#ifndef _POWERSPAWNRENDERER_H
#define _POWERSPAWNRENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PowerSpawnRenderer
// Utility class to draw the "Power Spawn" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PowerSpawnRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH                   = 140;      // Percentage of cell width
    static const int ENTITY_HEIGHT                  = 140;      // Percentage of cell height

    static const int BORDER_PEN_SCALE               = 6;        // Percentage of bounding rect width
    static const int INNER_CORE_PEN_SCALE           = 8;        // Percentage of bounding rect width
    static const int PROGRESS_PEN_SCALE             = 8;        // Percentage of bounding rect width

    static const int INNER_CORE_SCALE               = 90;       // Percentage of bounding rect
    static const int POWER_PROGRESS_SCALE           = 65;       // Percentage of bounding rect
    static const int ENERGY_STORE_SCALE             = 50;       // Percentage of bounding rect


public:

    PowerSpawnRenderer(QObject* parent = nullptr);
    virtual ~PowerSpawnRenderer();

    void setEnergy(int energy);
    void setEnergyCapacity(int energyCapacity);

    void setPower(int power);
    void setPowerCapacity(int powerCapacity);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    //
    // PowerSpawnRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    qreal _energy;
    qreal _power;

    qreal _energyCapacity;
    qreal _powerCapacity;
};


#endif // _POWERSPAWNRENDERER_H
