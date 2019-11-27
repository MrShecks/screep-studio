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

#include "CreepRenderer.h"
#include "../../../utils/JSONUtils.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor CreepRenderer1::BODY_COLOR            = QColor("#222222");
const QColor CreepRenderer1::ENERGY_COLOR          = QColor("#ffe56d");
const QColor CreepRenderer1::ENERGY_STORE_COLOR    = QColor("#555555");

const QColor CreepRenderer1::BODY_PART_COLOR[Screeps::BodyPart_Count] = {
    QColor("#aab7c5"),      // Move
    QColor("#fde574"),      // Work
    QColor("#56cf5e"),      // Heal
    QColor("#666666"),      // Carry
    QColor("#b99cfb"),      // Claim
    QColor("#555555"),      // Tough
    QColor("#f72e41"),      // Attack
    QColor("#7fa7e5")       // Ranged Attack
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreepRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CreepRenderer1::CreepRenderer1()
    : _energy(0),
      _energyCapacity(0),
      _isTough(false) {

}

CreepRenderer1::~CreepRenderer1() {

}

void CreepRenderer1::addBodyPart(Screeps::BodyPart part, int hitPoints /* = Screeps::MAX_CREEP_BODY_PART_HITS */) {
    if (hitPoints > 0) {
        switch(part) {
            case Screeps::BodyPart_Tough:
                _isTough = true;
            break;

            case Screeps::BodyPart_Carry:
                _energyCapacity += Screeps::CARRY_CAPACITY;
            break;

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

void CreepRenderer1::setEnergy(int energy, int energyCapacity) {
    Q_ASSERT(energy <= energyCapacity);

    _energy = energy;
    _energyCapacity = energyCapacity;
}

void CreepRenderer1::setTough(bool isTough) {
    _isTough = isTough;
}

CreepRenderer1& CreepRenderer1::setJson(const QJsonArray& json) {
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

void CreepRenderer1::reset() {
    _bodyParts.clear();
}

void CreepRenderer1::draw(QPainter* painter, qreal size, qreal angle /* = 0 */) {
    const qreal bodyRadius = ((size / 2) / 100) * CREEP_BODY_RADIUS;
    const qreal energyStoreRadius = ((size / 2) / 100) * CREEP_ENERGY_STORE_RADIUS;
    const qreal bodyPartLineWidth = (bodyRadius / 100) * CREEP_PART_LINE_WIDTH;
    const QPointF origin(0, 0);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->translate(size / 2, size / 2);
    painter->rotate (angle);

    painter->setBrush(BODY_COLOR);
    painter->drawEllipse(origin, bodyRadius, bodyRadius);
    painter->setPen(Qt::NoPen);

    if(_energy < _energyCapacity) {
        painter->setBrush(ENERGY_STORE_COLOR);
        painter->drawEllipse(origin, energyStoreRadius, energyStoreRadius);
    }

    if(_energy > 0) {
        const qreal energyRadius = energyStoreRadius * energyStorePercentage();

        painter->setBrush(ENERGY_COLOR);
        painter->drawEllipse(origin, energyRadius, energyRadius);
    }

    QRectF bodyPartRect = QRectF(-bodyRadius, -bodyRadius, bodyRadius * 2, bodyRadius * 2);

    if(_isTough)
        drawBodyPart(painter, bodyPartRect, BODY_PART_COLOR[Screeps::BodyPart_Tough], 360, bodyPartLineWidth / 2, false);

    TBodyPartList parts = sortedBodyParts();
    TBodyPartList::const_iterator it = parts.constBegin();
    TBodyPartList::const_iterator limit = parts.constEnd();

    for(; it != limit; ++it) {
        bool isBackPart = it->first == Screeps::BodyPart_Move;
        drawBodyPart(painter, bodyPartRect, BODY_PART_COLOR[it->first], it->second, bodyPartLineWidth, isBackPart);
    }

    painter->restore();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CreepRenderer1 CreepRenderer1::fromJson(const QJsonArray& json) {
    CreepRenderer1 renderer;

    return renderer.setJson(json);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qreal CreepRenderer1::energyStorePercentage() const {
    return  _energyCapacity > 0 ? (_energy / static_cast<qreal>(_energyCapacity)) : 0;
}

void CreepRenderer1::drawBodyPart(QPainter* painter, const QRectF& rect, QColor color, qreal size, qreal lineWidth, bool isBackendPart) {
    qreal startAngle = isBackendPart ? 270 : 90;

    painter->setPen(QPen(color, lineWidth));
    painter->drawArc(rect, (startAngle + (size /2)) * 16, -(size * 16));
}

CreepRenderer1::TBodyPartList CreepRenderer1::sortedBodyParts() const {
    TBodyPartMap::const_iterator it = _bodyParts.constBegin();
    TBodyPartMap::const_iterator limit = _bodyParts.constEnd();
    TBodyPartList parts;

    for(; it != limit; ++it) {
        parts.append (qMakePair(it.key(), it.value()));
    }

    std::sort(parts.begin(), parts.end(), CreepRenderer1::compare);

    return parts;
}

bool CreepRenderer1::compare(const TBodyPartList::value_type& a, const TBodyPartList::value_type& b) {
    return b.second < a.second;
}
