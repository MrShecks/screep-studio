/*
 * File: RoomGraphicsItemConstructionSite.cpp
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

#include <QPainter>

#include "RoomGraphicsItemConstructionSite.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsItemConstructionSite
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItemConstructionSite::RoomGraphicsItemConstructionSite(const ConstructionSiteEntity& entity, const QSize& cellSize, QGraphicsItem* parent /* = nullptr */)
    : _super(ItemType_ConstructionSite, entity, cellSize, ItemZOrder_ConstructionSite, parent),
      _opacityAnimation(new QPropertyAnimation(this)),
      _constructionSiteRenderer(this)  {

    _opacityAnimation->setTargetObject(this);
    _opacityAnimation->setPropertyName("opacity");

    _opacityAnimation->setKeyValueAt (0, 1.0);
    _opacityAnimation->setKeyValueAt (0.5, 0.3);
    _opacityAnimation->setKeyValueAt (1, 1.0);

    _opacityAnimation->setDuration(FADE_DURATION);
    _opacityAnimation->setLoopCount(-1);

    _opacityAnimation->start();

    _constructionSiteRenderer.setProgress(entity.progress(), entity.progressTotal());
}

RoomGraphicsItemConstructionSite::~RoomGraphicsItemConstructionSite() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF RoomGraphicsItemConstructionSite::itemSize(const QSize& cellSize) const {
    return _constructionSiteRenderer.size(cellSize);
}

void RoomGraphicsItemConstructionSite::paintItem(QPainter* painter, const QStyleOptionGraphicsItem* option, const QRectF& bounds) {
    _constructionSiteRenderer.draw(painter, bounds);

    Q_UNUSED(option);
}

bool RoomGraphicsItemConstructionSite::beginUpdate(const ConstructionSiteEntity& current, const ConstructionSiteEntity& updated) {

    if(current.progress() != updated.progress() || current.progressTotal() != updated.progressTotal())
        _constructionSiteRenderer.setProgress(updated.progress(), updated.progressTotal());

    return _constructionSiteRenderer.isDirty();
}
