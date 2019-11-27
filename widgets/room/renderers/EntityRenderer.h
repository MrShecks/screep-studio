/*
 * File: EntityRenderer.h
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

#ifndef _ENTITYRENDERER_H
#define _ENTITYRENDERER_H

#include <QObject>
#include <QSizeF>
#include <QHash>
#include <QColor>

#include "../ScreepsApi.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class QPainter;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EntityRenderer
// Base class for room entity drawing
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class EntityRenderer : public QObject {
    typedef QObject _super;

public:
    enum OwnerType {
        OwnerType_None,
        OwnerType_Player,
        OwnerType_Enemy
    };

    enum PaletteColor {
        Color_Black,
        Color_Gray,

        Color_Player_Owned,
        Color_Enemy_Owned,
        Color_Not_Owned,

        Color_Controller_Base,
        Color_Controller_Level_Segment,

        Color_Energy,
        Color_EnergyStore,

        Color_Stored_Power,
        Color_Stored_Resource,

        Color_Spawn_Base,
        Color_Spawn_Border,
        Color_Spawn_Progress,

        Color_PowerSpawn_Base,
        Color_PowerSpawn_Outer_Border,
        Color_PowerSpawn_Inner_Border,
        Color_PowerSpawn_Progress,

        Color_Creep_Body_Base,
        Color_Creep_Body_Move,
        Color_Creep_Body_Work,
        Color_Creep_Body_Heal,
        Color_Creep_Body_Carry,
        Color_Creep_Body_Claim,
        Color_Creep_Body_Tough,
        Color_Creep_Body_Attack,
        Color_Creep_Body_Ranged_Attack,

        Color_Creep_Npc_Base,
        Color_Creep_Npc_Border,

        Color_Tower_Base,
        Color_Tower_Turret,

        Color_Tombstone,
        Color_Tombstone_Border,

        Color_Player_Rampart,
        Color_Player_Rampart_Border,

        Color_Enemy_Rampart,
        Color_Enemy_Rampart_Border,

        Color_Observer_Base,

        Color_Wall,

        Color_Road
    };

    EntityRenderer(QObject* parent = nullptr);
    virtual ~EntityRenderer();

    bool isDirty() const;
    bool isPlayerOwned() const;

    void setOwner(OwnerType ownerType);

    virtual QSizeF size(const QSize& cellSize) const = 0;
    virtual void draw(QPainter* painter, const QRectF& bounds) const = 0;

    virtual QImage drawImage(const QSize& size, QColor bgColor = Qt::black, const QSize& border = QSize()) const;

    static EntityRenderer* create(Screeps::EntityType entityType, QObject* parent = nullptr);

protected:
    qreal scaledWidth(const QSizeF& size, qreal percent) const;
    qreal scaledHeight(const QSizeF& size, qreal percent) const;

    QRectF scaledRect(const QRectF& rect, int percent) const;
    QRectF scaledRect(const QRectF& rect, int widthPercent, int heightPercent) const;

    QRectF scaledRect(const QRectF& rect, qreal scale) const;
    QRectF scaledRect(const QRectF& rect, qreal widthScale, qreal heightScale) const;

    QColor paletteColor(PaletteColor index, QColor defaultColor = Qt::white) const;
    QColor playerColor() const;

    void setDirty(bool isDirty) const;

private:
    typedef QHash<int, QColor> TColorPalette;

    OwnerType _ownerType;
    mutable bool _isDirty;

    static const TColorPalette _colorPalette;
};

#endif // _ENTITYRENDERER_H
