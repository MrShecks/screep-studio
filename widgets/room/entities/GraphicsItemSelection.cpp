/*
 * File: GraphicsItemSelection.cpp
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

#include <QPainter>

#include "GraphicsItemSelection.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor GraphicsItemSelection::SELECTION_PEN_COLOR     = QColor("#5763a2");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphicsItemSelection
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GraphicsItemSelection::GraphicsItemSelection(QGraphicsItem* parent)
    : _super(parent) {

    Q_ASSERT(parent != nullptr);

    setVisible(false);
    setFlag (QGraphicsItem::ItemIgnoresParentOpacity, true);
    setZValue(1000000);
    setTransformOriginPoint(0, 0);
}

GraphicsItemSelection::~GraphicsItemSelection() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QRectF GraphicsItemSelection::boundingRect() const {
    const QGraphicsItem* parent = parentItem();
    Q_ASSERT(parent != nullptr);

    return parent->boundingRect().adjusted(-(SELECTION_PADDING + SELECTTION_HALF_PEN_WIDTH),
                                           -(SELECTION_PADDING + SELECTTION_HALF_PEN_WIDTH),
                                           SELECTION_PADDING + SELECTTION_HALF_PEN_WIDTH,
                                           SELECTION_PADDING + SELECTTION_HALF_PEN_WIDTH);
}

void GraphicsItemSelection::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    const QRectF bounds = boundingRect().adjusted (SELECTTION_HALF_PEN_WIDTH, SELECTTION_HALF_PEN_WIDTH, -SELECTTION_HALF_PEN_WIDTH, -SELECTTION_HALF_PEN_WIDTH);

    painter->setPen(QPen(SELECTION_PEN_COLOR, SELECTION_PEN_WIDTH, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(bounds);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
