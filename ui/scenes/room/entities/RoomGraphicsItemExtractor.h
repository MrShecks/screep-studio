/*
 * File: RoomGraphicsItemExtractor.h
 * Created: 2019-1-9
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

#ifndef _ROOMGRAPHICSITEMEXTRACTOR_H
#define _ROOMGRAPHICSITEMEXTRACTOR_H

#include <QPropertyAnimation>

#include "RoomGraphicsItem.h"
#include "ui/scenes/room/renderers/ExtractorRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ExtractorEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ExtractorEntity : public RoomEntity {
    typedef RoomEntity _super;

public:
    ExtractorEntity(const RoomEntity& entity)
        : _super(entity) {

    }

    int cooldown() const                        { return getInt("cooldown"); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemExtractor
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemExtractor : public TRoomGraphicsItem<ExtractorEntity> {
    typedef TRoomGraphicsItem<ExtractorEntity> _super;

    Q_OBJECT
    Q_PROPERTY(qreal extractorRotation READ extractorRotation WRITE setExtractorRotation)

    static const int ROTATE_ANIMATION_DURATION = 1000 * 5;

public:
    RoomGraphicsItemExtractor(const ExtractorEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemExtractor();

    qreal extractorRotation() const;
    void setExtractorRotation(qreal extractorRotation);

private:
    ExtractorRenderer _extractorRenderer;
    QPropertyAnimation _rotationAnimator;

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const ExtractorEntity& current, const ExtractorEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMEXTRACTOR_H
