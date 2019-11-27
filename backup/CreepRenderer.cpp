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

#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor CreepRenderer::BODY_COLOR            = QColor("#222222");
const QColor CreepRenderer::ENERGY_COLOR          = QColor("#ffe56d");
const QColor CreepRenderer::ENERGY_STORE_COLOR    = QColor("#555555");

const QColor CreepRenderer::BODY_PART_COLOR[Screeps::BodyPart_Count] = {
    QColor("#aab7c5"),      // Move
    QColor("#fde574"),      // Work
    QColor("#666666"),      // Carry
    QColor("#f72e41"),      // Attack
    QColor("#7fa7e5"),      // Ranged Attack
    QColor("#56cf5e"),      // Heal
    QColor("#b99cfb"),      // Claim
    QColor("#555555")       // Tough
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreepRenderer
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CreepRenderer::CreepRenderer()
    : _energy(0),
      _energyCapacity(0),
      _isTough(false) {

}

CreepRenderer::~CreepRenderer() {

}

void CreepRenderer::addBodyPart(Screeps::BodyPart part, int hitPoints /* = Screeps::MAX_CREEP_BODY_PART_HITS */) {
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

void CreepRenderer::setEnergy(int energy, int energyCapacity) {
    Q_ASSERT(energy <= energyCapacity);

    _energy = energy;
    _energyCapacity = energyCapacity;
}

void CreepRenderer::setTough(bool isTough) {
    _isTough = isTough;
}

void CreepRenderer::setJson(const QJsonArray& json) {
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
}

void CreepRenderer::reset() {
    _bodyParts.clear();
}

void CreepRenderer::draw(QPainter* painter, int size) {
    const qreal totalRadius = size / 2;
    QRectF bounds = QRect(0, 0, size, size);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    qreal radius = bodyPartScaleSize(totalRadius, CREEP_BASE_RADIUS);

    painter->setBrush(BODY_COLOR);
    painter->drawEllipse(bounds.center(), radius, radius);
    painter->setPen(Qt::NoPen);

    radius = (totalRadius / 100) * CREEP_ENERGY_STORE_RADIUS;
    painter->setBrush(ENERGY_STORE_COLOR);
    painter->drawEllipse(bounds.center(), radius, radius);

    radius = (totalRadius / 100) * (CREEP_ENERGY_STORE_RADIUS * energyStorePercentage());
    painter->setBrush(ENERGY_COLOR);
    painter->drawEllipse(bounds.center(), radius, radius);

    radius = (totalRadius / 100) * CREEP_BASE_RADIUS;
    QRectF partRect = bounds;

    radius = (totalRadius / 100) * (100 - CREEP_BASE_RADIUS);
    partRect = bounds.adjusted (radius, radius, -radius, -radius);

    qreal height = (totalRadius / 100) * CREEP_PART_LINE_WIDTH;

    if(_isTough)
        drawBodyPart(painter, partRect, BODY_PART_COLOR[Screeps::BodyPart_Tough], 360, height / 2, false);

    TBodyPartList parts = sortedBodyParts();
    TBodyPartList::const_iterator it = parts.constBegin();
    TBodyPartList::const_iterator limit = parts.constEnd();

    for(; it != limit; ++it) {
        bool isBackPart = it->first == Screeps::BodyPart_Move;
        drawBodyPart(painter, partRect, BODY_PART_COLOR[it->first], it->second, height, isBackPart);

//        qDebug() << "CreepRenderer::draw(): BodyPart=" << it->first << ", Size=" << it->second;
    }

    painter->restore();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CreepRenderer CreepRenderer::fromJson(const QJsonArray& json) {
    CreepRenderer renderer;

    renderer.setJson(json);

    return renderer;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

qreal CreepRenderer::energyStorePercentage() const {
    return  _energyCapacity > 0 ? (_energy / static_cast<qreal>(_energyCapacity)) : 0;
}

qreal CreepRenderer::bodyPartScaleSize(qreal totalRadius, int partScale) const {
    return (totalRadius / 100) * partScale;
}

void CreepRenderer::drawBodyPart(QPainter* painter, const QRectF& rect, QColor color, qreal size, qreal height, bool isBackendPart) {
    qreal startAngle = isBackendPart ? 270 : 90;

    painter->setPen(QPen(color, height));
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
