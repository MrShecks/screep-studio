/*
 * File: RoomGraphicsItemConstructionSite.h
 * Created: 2018-12-11
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

#ifndef _ROOMGRAPHICSITEMCONSTRUCTIONSITE_H
#define _ROOMGRAPHICSITEMCONSTRUCTIONSITE_H

#include <QPropertyAnimation>

#include "RoomGraphicsItem.h"
#include "../renderers/ConstructionSiteRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConstructionSiteEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ConstructionSiteEntity : public RoomEntity {
    typedef RoomEntity _super;

public:
    ConstructionSiteEntity(const RoomEntity& entity)
        : _super(entity) {
    }

    int progress() const                        { return getInt("progress"); }
    int progressTotal() const                   { return getInt("progressTotal"); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemConstructionSite
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsItemConstructionSite : public TRoomGraphicsItem<ConstructionSiteEntity> {
    typedef TRoomGraphicsItem<ConstructionSiteEntity> _super;

    static const int FADE_DURATION                  = 1000 * 3;

public:
    RoomGraphicsItemConstructionSite(const ConstructionSiteEntity& entity, const QSize& cellSize, QGraphicsItem* parent = nullptr);
    virtual ~RoomGraphicsItemConstructionSite();

private:
    QPropertyAnimation* _opacityAnimation;
    ConstructionSiteRenderer _constructionSiteRenderer;

    //
    // TRoomGraphicsItem
    //

    QSizeF itemSize(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) Q_DECL_OVERRIDE;
    bool beginUpdate(const ConstructionSiteEntity& current, const ConstructionSiteEntity& updated) Q_DECL_OVERRIDE;
};

#endif // _ROOMGRAPHICSITEMCONSTRUCTIONSITE_H
