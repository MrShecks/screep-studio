/*
 * File: EnergyRenderer.h
 * Created: 2019-1-18
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

#ifndef _ENERGYRENDERER_H
#define _ENERGYRENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EnergyRenderer
// Utility class to draw the "dropped energy" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EnergyRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH               = 40;       // Percentage of cell width
    static const int ENTITY_HEIGHT              = 40;       // Percentage of cell height

public:

    EnergyRenderer(QObject* parent = nullptr);
    virtual ~EnergyRenderer();

    void setEnergy(int energy);
    void setEnergyCapacity(int energyCapacity);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

private:
    qreal _energy;
    qreal _energyCapacity;
};

#endif // _ENERGYRENDERER_H
