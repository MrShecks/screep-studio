/*
 * File: ExtensionRenderer.h
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

#ifndef _EXTENSIONRENDERER_H
#define _EXTENSIONRENDERER_H

#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ExtensionRenderer
// Utility class to draw the "Extension" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ExtensionRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int SMALL_ENTITY_SIZE          = 60;       // Percentage of cell width
    static const int MEDIUM_ENTITY_SIZE         = 80;       // Percentage of cell width
    static const int LARGE_ENTITY_SIZE          = 100;      // Percentage of cell width

    static const int BORDER_PEN_WIDTH           = 4;        // Pixels

    static const int ENERGY_STORE_SIZE          = 70;       // Percentage of bounding rect width

public:

    ExtensionRenderer(QObject* parent = nullptr);
    virtual ~ExtensionRenderer();

    void setEnergy(int energy);
    void setEnergyCapacity(int energyCapacity);

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    //
    // ExtensionRenderer
    //

    static QImage toImage(const QSize& size, QColor fillColor = Qt::white, const QSize& border = QSize());

private:
    qreal _energy;
    qreal _energyCapacity;

    int getExtensionSize(int energyCapacity) const;
};

#endif // _EXTENSIONRENDERER_H
