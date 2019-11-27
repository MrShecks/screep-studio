/*
 * File: CreepRenderer.h
 * Created: 2018-12-15
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

#ifndef _CREEPRENDERER_H
#define _CREEPRENDERER_H

#include <QPainter>
#include <QColor>
#include <QList>
#include <QPair>
#include <QMap>
#include <QJsonArray>

#include "ScreepsApi.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreepRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CreepRenderer {

    static const int CREEP_BASE_RADIUS          = 80;       // Percentage of total radius
    static const int CREEP_ENERGY_STORE_RADIUS  = 50;       // Percentage of total radius
    static const int CREEP_PART_LINE_WIDTH      = 30;       // Percentage of total radius

public:

    CreepRenderer();
    virtual ~CreepRenderer();

    void addBodyPart(Screeps::BodyPart part, int hitPoints = Screeps::MAX_CREEP_BODY_PART_HITS);

    void setEnergy(int energy, int energyCapacity);
    void setTough(bool isTough);

    void setJson(const QJsonArray& json);

    void reset();

    void draw(QPainter* painter, int size);

    static CreepRenderer fromJson(const QJsonArray& json);

private:
    typedef QMap<Screeps::BodyPart, qreal> TBodyPartMap;
    typedef QList<QPair<Screeps::BodyPart, qreal>> TBodyPartList;

    static const QColor BODY_COLOR;
    static const QColor ENERGY_COLOR;
    static const QColor ENERGY_STORE_COLOR;

    static const QColor BODY_PART_COLOR[Screeps::BodyPart_Count];

    int _energy;
    int _energyCapacity;

    bool _isTough;

    TBodyPartMap _bodyParts;

    qreal energyStorePercentage() const;
    qreal bodyPartScaleSize(qreal totalRadius, int partScale) const;

    void drawBodyPart(QPainter* painter, const QRectF& rect, QColor color, qreal size, qreal height, bool isBackendPart);

    TBodyPartList sortedBodyParts() const;

    static bool compare(const TBodyPartList::value_type &a, const TBodyPartList::value_type &b);
};

#endif // _CREEPRENDERER_H
