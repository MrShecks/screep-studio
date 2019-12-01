/*
 * File: CreepRenderer.cpp
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

#include <QPainterPath>

#include "CreepRenderer.h"
#include "utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// Note: Colors should be defined in the same order as the Screeps::BodyPart enum
//

const CreepRenderer::PaletteColor CreepRenderer::BODY_PART_COLOR[Screeps::BodyPart_Count] = {
    Color_Creep_Body_Move,              // Screeps::BodyPart_Move
    Color_Creep_Body_Work,              // Screeps::BodyPart_Work
    Color_Creep_Body_Heal,              // Screeps::BodyPart_Heal
    Color_Creep_Body_Carry,             // Screeps::BodyPart_Carry
    Color_Creep_Body_Claim,             // Screeps::BodyPart_Claim
    Color_Creep_Body_Tough,             // Screeps::BodyPart_Tough
    Color_Creep_Body_Attack,            // Screeps::BodyPart_Attack
    Color_Creep_Body_Ranged_Attack      // Screeps::BodyPart_Ranged_Attack
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreepRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CreepRenderer::CreepRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _energy(0),
      _energyCapacity(0),
      _isTough(false),
      _isNpc(false),
      _rotation(0) {

}

CreepRenderer::~CreepRenderer() {

}

void CreepRenderer::addBodyPart(Screeps::BodyPart part, int hitPoints /* = Screeps::MAX_CREEP_BODY_PART_HITS */) {
    if (hitPoints > 0) {
        switch(part) {
            case Screeps::BodyPart_Tough:
                _isTough = true;
            break;

//            case Screeps::BodyPart_Carry:
//                _energyCapacity += Screeps::CARRY_CAPACITY;
//            break;

            default: {
                qreal partSize = (360.0f / Screeps::MAX_CREEP_BODY_PARTS) * (hitPoints / static_cast<qreal> (Screeps::MAX_CREEP_BODY_PART_HITS));
                TBodyPartMap::iterator it;

                if((it = _bodyParts.find(part)) != _bodyParts.end())
                    it.value () = it.value () + partSize;
                else
                    _bodyParts.insert (part, partSize);
            }
            break;
        }
    }
}

void CreepRenderer::setNpc(bool isNpc) {
    _isNpc = isNpc;
    setDirty(true);
}

void CreepRenderer::setEnergy(int energy) {
    _energy = energy;
    setDirty(true);
}

void CreepRenderer::setEnergyCapacity(int energyCapacity) {
    _energyCapacity = energyCapacity;
    setDirty(true);
}

void CreepRenderer::setTough(bool isTough) {
    _isTough = isTough;
    setDirty(true);
}

void CreepRenderer::setRotation(qreal rotation) {
    _rotation = rotation;
    setDirty(true);
}

CreepRenderer& CreepRenderer::setJson(const QJsonArray& json) {
    QJsonArray::const_iterator it = json.constBegin();
    QJsonArray::const_iterator limit = json.constEnd();

    _bodyParts.clear();

    for(; it != limit; ++it) {
        if(it->isObject ()) {
            const QJsonObject& bodyPart = it->toObject();
            Screeps::BodyPart partType = Screeps::getBodyPart(JSONUtils::getString(bodyPart, "type"));
            Q_ASSERT(partType != Screeps::BodyPart_Unknown);

            addBodyPart(partType, JSONUtils::getInt(bodyPart, "hits"));
        }
    }

    return *this;
}

void CreepRenderer::reset() {
    _bodyParts.clear();
}

QSizeF CreepRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSizeF(width, height);
}

void CreepRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const QRectF baseRect = bounds.translated(-bounds.center());

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->translate(bounds.center());
    painter->rotate (_rotation);

    if(!_isNpc)
        drawPlayerCreep(painter, baseRect);
    else
        drawNonPlayerCreep(painter, scaledRect(baseRect, NPC_SIZE_SCALE));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CreepRenderer CreepRenderer::fromJson(const QJsonArray& json, const QSize& cellSize, QObject* parent /* = nullptr */) {
    CreepRenderer renderer(parent);

    return renderer.setJson(json);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CreepRenderer::CreepRenderer(const CreepRenderer& other)
    : _super(other.parent()) {

}

void CreepRenderer::drawPlayerCreep(QPainter* painter, const QRectF& bounds) const {

    //
    // TODO: Handle rendering power creeps
    //

    const QRectF energyStoreRect = scaledRect(bounds, ENERGY_STORE_SIZE_SCALE);
    const QRectF bodyPartRect = scaledRect(bounds, BODY_PART_SIZE_SCALE);
    const qreal bodyPartPenHeight = scaledHeight(bounds.size(), BODY_PART_PEN_SCALE);

    painter->setBrush(paletteColor(Color_Creep_Body_Base));
    painter->drawEllipse(bounds);
    painter->setPen(Qt::NoPen);

    if(_energy < _energyCapacity) {
        painter->setBrush(paletteColor(Color_EnergyStore));
        painter->drawEllipse(energyStoreRect);
    }

    if(_energy > 0 && _energy <= _energyCapacity) {
        const QRectF energyRect = scaledRect(energyStoreRect, _energy / _energyCapacity);

        painter->setBrush(paletteColor(Color_Energy));
        painter->drawEllipse(energyRect);
    }

    if(_isTough)
        drawBodyPart(painter, bodyPartRect, BODY_PART_COLOR[Screeps::BodyPart_Tough], 360, bodyPartPenHeight / 2, false);

    TBodyPartList parts = sortedBodyParts();
    TBodyPartList::const_iterator it = parts.constBegin();
    TBodyPartList::const_iterator limit = parts.constEnd();

    for(; it != limit; ++it) {
        bool isBackPart = it->first == Screeps::BodyPart_Move;
        drawBodyPart(painter, bodyPartRect, BODY_PART_COLOR[it->first], it->second, bodyPartPenHeight, isBackPart);
    }
}

void CreepRenderer::drawNonPlayerCreep(QPainter* painter, const QRectF& bounds) const {
    const qreal sectionWidth = bounds.width() / 4;
    const qreal sectionHeight = bounds.height() / 4;
    QPainterPath path;

    path.moveTo(bounds.center().x(), bounds.top());

    path.lineTo(bounds.right(), bounds.bottom() - sectionHeight);
    path.lineTo(bounds.right() - sectionWidth, bounds.bottom());
    path.lineTo(bounds.left() + sectionWidth, bounds.bottom());
    path.lineTo(bounds.left(), bounds.bottom() - sectionHeight);
    path.closeSubpath();

    painter->setPen(QPen(paletteColor(Color_Creep_Npc_Border), BORDER_PEN_WIDTH, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
    painter->setBrush(paletteColor(Color_Creep_Npc_Base));
    painter->drawPath(path);
}

void CreepRenderer::drawBodyPart(QPainter* painter, const QRectF& rect, PaletteColor colorIndex, qreal size, qreal lineWidth, bool isBackendPart) const {
    const qreal startAngle = isBackendPart ? 270 : 90;
    const QColor color = paletteColor(colorIndex);

    painter->setPen(QPen(color, lineWidth));
    painter->drawArc(rect, (startAngle + (size /2)) * 16, -(size * 16));
}

CreepRenderer::TBodyPartList CreepRenderer::sortedBodyParts() const {
    TBodyPartMap::const_iterator it = _bodyParts.constBegin();
    TBodyPartMap::const_iterator limit = _bodyParts.constEnd();
    TBodyPartList parts;

    for(; it != limit; ++it) {
        parts.append (qMakePair(it.key(), it.value()));
    }

    std::sort(parts.begin(), parts.end(), CreepRenderer::compare);

    return parts;
}

bool CreepRenderer::compare(const TBodyPartList::value_type& a, const TBodyPartList::value_type& b) {
    return b.second < a.second;
}
