/*
 * File: EntityRenderer.cpp
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

#include "EntityRenderer.h"
#include "CreepRenderer.h"
#include "SourceRenderer.h"
#include "ExtensionRenderer.h"
#include "MineralRenderer.h"
#include "SpawnRenderer.h"
#include "TombstoneRenderer.h"
#include "TowerRenderer.h"
#include "ConstructionSiteRenderer.h"
#include "UnknownRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const EntityRenderer::TColorPalette EntityRenderer::_colorPalette = {
    { Color_Black,                      QColor(Qt::black)       },
    { Color_Gray,                       QColor(Qt::gray)        },

    { Color_Player_Owned,               QColor("#8fbb93")       },        // Colour used if the player owns the entity
    { Color_Enemy_Owned,                QColor("#ff7777")       },        // Colour used if another player owns the entity
    { Color_Not_Owned,                  QColor("#bbbbbb")       },        // Colour used if the entity is un-owned

    { Color_Controller_Base,            QColor("#080808")       },
    { Color_Controller_Level_Segment,   QColor("#ffffff")       },

    { Color_Energy,                     QColor("#ffe56d")       },
    { Color_EnergyStore,                QColor("#555555")       },

    { Color_Stored_Power,               QColor("#f41f33")       },
    { Color_Stored_Resource,            QColor("#ffffff")       },

    { Color_Spawn_Base,                 QColor(Qt::black)       },
    { Color_Spawn_Border,               QColor("#cccccc")       },
    { Color_Spawn_Progress,             QColor("#cccccc")       },

    { Color_PowerSpawn_Base,            QColor("#222222")       },
    { Color_PowerSpawn_Outer_Border,    QColor("#cccccc")       },
    { Color_PowerSpawn_Inner_Border,    QColor("#f41f33")       },
    { Color_PowerSpawn_Progress,        QColor("#f41f33")       },

    { Color_Creep_Body_Base,            QColor("#222222")       },
    { Color_Creep_Body_Move,            QColor("#aab7c5")       },
    { Color_Creep_Body_Work,            QColor("#fde574")       },
    { Color_Creep_Body_Heal,            QColor("#56cf5e")       },
    { Color_Creep_Body_Carry,           QColor("#666666")       },
    { Color_Creep_Body_Claim,           QColor("#b99cfb")       },
    { Color_Creep_Body_Tough,           QColor("#555555")       },
    { Color_Creep_Body_Attack,          QColor("#f72e41")       },
    { Color_Creep_Body_Ranged_Attack,   QColor("#7fa7e5")       },

    { Color_Creep_Npc_Base,             QColor("#f93842")       },
    { Color_Creep_Npc_Border,           QColor(Qt::black)       },

    { Color_Tower_Base,                 QColor("#222222")       },
    { Color_Tower_Turret,               QColor("#cccccc")       },

    { Color_Tombstone,                  QColor(Qt::transparent) },
    { Color_Tombstone_Border,           QColor("#fff3ff")       },

    { Color_Player_Rampart,             QColor("#105010")       },
    { Color_Player_Rampart_Border,      QColor("#44ff44")       },

    { Color_Enemy_Rampart,              QColor("#501010")       },
    { Color_Enemy_Rampart_Border,       QColor("#ff4444")       },

    { Color_Observer_Base,              QColor("#111111")       },

    { Color_Wall,                       QColor("#111111")       },

    { Color_Road,                       QColor("#aaaaaa")       }

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// EntityRenderer
// Base class for room entity drawing
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

EntityRenderer::EntityRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _ownerType(OwnerType_Enemy),
      _isDirty(false) {

}

EntityRenderer::~EntityRenderer() {

}

bool EntityRenderer::isDirty() const {
    return _isDirty;
}

bool EntityRenderer::isPlayerOwned() const {
    return _ownerType == OwnerType_Player;
}

void EntityRenderer::setOwner(OwnerType ownerType) {
    _ownerType = ownerType;
}

QImage EntityRenderer::drawImage(const QSize& size, QColor bgColor /* = Qt::black */, const QSize& border /* = QSize() */) const {
    const QRectF bounds = QRectF(0, 0, size.width(), size.height());
    QImage image(size, QImage::Format_RGB32);
    QPainter painter(&image);

    painter.setRenderHint (QPainter::Antialiasing, true);
    painter.fillRect (bounds, bgColor);

    draw(&painter, bounds.adjusted(border.width(), border.height(), -border.width(), -border.height()));

    return image;
}

EntityRenderer* EntityRenderer::create(Screeps::EntityType entityType, QObject* parent /* = nullptr */) {
    EntityRenderer* renderer = nullptr;

    switch(entityType) {
        case Screeps::EntityType_Creep:                 renderer = new CreepRenderer(parent);                 break;
        case Screeps::EntityType_Source:                renderer = new SourceRenderer(parent);                break;
        case Screeps::EntityType_Extension:             renderer = new ExtensionRenderer(parent);             break;
        case Screeps::EntityType_Mineral:               renderer = new MineralRenderer(parent);               break;
        case Screeps::EntityType_Spawn:                 renderer = new SpawnRenderer(parent);                 break;
        case Screeps::EntityType_Tombstone:             renderer = new TombstoneRenderer(parent);             break;
        case Screeps::EntityType_Tower:                 renderer = new TowerRenderer(parent);                 break;
        case Screeps::EntityType_ConstructionSite:      renderer = new ConstructionSiteRenderer(parent);      break;

        default:                                        renderer = new UnknownRenderer(parent);               break;
    }

    return renderer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qreal EntityRenderer::scaledWidth(const QSizeF& size, qreal percent) const {
    return size.width() * (percent / 100.0f);
}

qreal EntityRenderer::scaledHeight(const QSizeF& size, qreal percent) const {
    return size.height() * (percent / 100.0f);
}

QRectF EntityRenderer::scaledRect(const QRectF &rect, int percent) const {
    return scaledRect(rect, percent / 100.0f);
}

QRectF EntityRenderer::scaledRect(const QRectF& rect, int wpercent, int hpercent) const {
    return scaledRect(rect, wpercent / 100.0f, hpercent / 100.0f);
}

QRectF EntityRenderer::scaledRect(const QRectF& rect, qreal scale) const {
    return scaledRect(rect, scale, scale);
}

QRectF EntityRenderer::scaledRect(const QRectF& rect, qreal wscale, qreal hscale) const {
    const qreal width = rect.width() * wscale;
    const qreal height = rect.height() * hscale;

    return QRectF(
        rect.center().x() - (width / 2),
        rect.center().y() - (height / 2),
        width,
        height
    );
}

QColor EntityRenderer::paletteColor(PaletteColor index, QColor defaultColor /* = Qt::white */) const {
    return EntityRenderer::_colorPalette.value(index, defaultColor);
}

QColor EntityRenderer::playerColor() const {
    QColor color;

    switch(_ownerType) {
        case OwnerType_Player:  color = EntityRenderer::_colorPalette.value(Color_Player_Owned);    break;
        case OwnerType_Enemy:   color = EntityRenderer::_colorPalette.value(Color_Enemy_Owned);     break;
        default:                color = EntityRenderer::_colorPalette.value(Color_Not_Owned);       break;
    }

    return color;
}

void EntityRenderer::setDirty(bool isDirty) const {
    _isDirty = isDirty;
}
