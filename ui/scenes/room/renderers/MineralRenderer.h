/*
 * File: MineralRenderer.h
 * Created: 2018-12-28
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

#ifndef _MINERALRENDERER_H
#define _MINERALRENDERER_H

#include <QHash>

#include "ScreepsApi.h"
#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MineralRenderer
// Utility class to draw the "Mineral" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MineralRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH               = 100;      // Percentage of cell width
    static const int ENTITY_HEIGHT              = 100;      // Percentage of cell height

    static const int BORDER_PEN_WIDTH           = 4;        // Pixels

    static const int FONT_SIZE_SCALE            = 50;       // Percentage of bounding rect

public:

    MineralRenderer(QObject* parent = nullptr);
    virtual ~MineralRenderer();

    void setMineralType(const QString& mineralType);

    QColor foregroundColor() const;
    QColor backgroundColor() const;

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

private:
    typedef QHash<QString, QColor> TMineralColorMap;

    QString _mineralType;
    QColor _foregroundColor;
    QColor _backgroundColor;

    static const TMineralColorMap _FOREGROUND_COLORS;
    static const TMineralColorMap _BACKGROUND_COLORS;

    QColor foregroundColor(const QString& mineralType, QColor defaultColor = Qt::white) const;
    QColor backgroundColor(const QString& mineralType, QColor defaultColor = Qt::black) const;
};

#endif // _MINERALRENDERER_H
