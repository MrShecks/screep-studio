/*
 * File: SpawnRenderer.h
 * Created: 2018-12-27
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

#ifndef _SPAWNRENDERER_H
#define _SPAWNRENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SpawnRenderer
// Utility class to draw the "Spawn" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SpawnRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH                   = 140;      // Percentage of cell width
    static const int ENTITY_HEIGHT                  = 140;      // Percentage of cell height

    static const int BORDER_PEN_SCALE               = 4;        // Percentage of bounding rect width
    static const int PROGRESS_PEN_SCALE             = 8;        // Percentage of bounding rect width

    static const int ENERGY_STORE_SCALE             = 60;       // Percentage of bounding rect
    static const int SPAWN_PROGRESS_SCALE           = 75;       // Percentage of bounding rect

public:

    SpawnRenderer(QObject* parent = nullptr);
    virtual ~SpawnRenderer();

    void setEnergy(int energy);
    void setEnergyCapacity(int energyCapacity);

    void setSpawnProgress(int elapsedSpawnTime, int totalSpawnTime);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    //
    // SpawnRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    qreal _energy;
    qreal _energyCapacity;

    int _elapsedSpawnTime;
    int _totalSpawnTime;
};

#endif // _SPAWNRENDERER_H
