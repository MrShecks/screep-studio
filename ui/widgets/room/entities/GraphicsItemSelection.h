/*
 * File: GraphicsItemSelection.h
 * Created: 2018-12-19
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

#ifndef _GRAPHICSITEMSELECTION_H
#define _GRAPHICSITEMSELECTION_H

#include <QGraphicsItem>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphicsItemSelection
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GraphicsItemSelection : public QGraphicsItem {
    typedef QGraphicsItem _super;

    static constexpr qreal SELECTION_PADDING            = 4;

    static constexpr qreal SELECTION_PEN_WIDTH          = 4;
    static constexpr qreal SELECTTION_HALF_PEN_WIDTH    = SELECTION_PEN_WIDTH / 2;

    static const QColor SELECTION_PEN_COLOR;

public:
    GraphicsItemSelection(QGraphicsItem* parent);
    virtual ~GraphicsItemSelection();

    //
    // QGraphicsItem
    //

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) Q_DECL_OVERRIDE;

};

#endif // _GRAPHICSITEMSELECTION_H
