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
#include "EntityRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreepRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CreepRenderer : public EntityRenderer {
    typedef EntityRenderer _super;

    static const int ENTITY_WIDTH               = 80;                               // Percentage of cell width
    static const int ENTITY_HEIGHT              = 80;                               // Percentage of cell height

    static const int BORDER_PEN_WIDTH           = 8;                                // Pixels

    static const int ENERGY_STORE_SIZE_SCALE    = 65;                               // Percentage of bounding rect

    static const int BODY_PART_PEN_SCALE        = 14;                               // Percentage of bounding rect
    static const int BODY_PART_SIZE_SCALE       = 100 - BODY_PART_PEN_SCALE;        // Percentage of bounding rect

    static const int NPC_SIZE_SCALE             = 90;                               // Percentage of bounding rect
    static const int NPC_BORDER_PEN_WIDTH       = 6;                                // Pixels

public:

    CreepRenderer(QObject* parent = nullptr);
    virtual ~CreepRenderer();

    void addBodyPart(Screeps::BodyPart part, int hitPoints = Screeps::MAX_CREEP_BODY_PART_HITS);

    void setNpc(bool isNpc);

    void setEnergy(int energy);
    void setEnergyCapacity(int energyCapacity);

    void setTough(bool isTough);

    void setRotation(qreal rotation);

    CreepRenderer& setJson(const QJsonArray& json);

    void reset();

    //
    // EntityRenderer
    //

    QSizeF size(const QSize& cellSize) const Q_DECL_OVERRIDE;
    void draw(QPainter* painter, const QRectF& bounds) const Q_DECL_OVERRIDE;

    static CreepRenderer fromJson(const QJsonArray& json, const QSize& cellSize, QObject* parent = nullptr);

private:
    typedef QMap<Screeps::BodyPart, qreal> TBodyPartMap;
    typedef QList<QPair<Screeps::BodyPart, qreal>> TBodyPartList;

    static const PaletteColor BODY_PART_COLOR[Screeps::BodyPart_Count];

    qreal _energy;
    qreal _energyCapacity;

    bool _isTough;
    bool _isNpc;

    qreal _rotation;

    TBodyPartMap _bodyParts;

    CreepRenderer(const CreepRenderer& other);

    void drawPlayerCreep(QPainter* painter, const QRectF& bounds) const;
    void drawNonPlayerCreep(QPainter* painter, const QRectF& bounds) const;

    void drawBodyPart(QPainter* painter, const QRectF& rect, PaletteColor colorIndex, qreal size, qreal lineWidth, bool isBackendPart) const;

    TBodyPartList sortedBodyParts() const;

    static bool compare(const TBodyPartList::value_type &a, const TBodyPartList::value_type &b);
};

#endif // _CREEPRENDERER_H
