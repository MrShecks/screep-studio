/*
 * File: GraphicsItemLaserBeam.cpp
 * Created: 2018-12-30
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

#include <QPen>
#include <QGraphicsScene>

#include "GraphicsItemEnergyBeam.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor GraphicsItemEnergyBeam::_COLORS[GraphicsItemEnergyBeam::EnergyType_Count] = {
    QColor("#65fd62"),      // EnergyType_Heal
    QColor("#ffe56d"),      // EnergyType_Repair
    QColor("#5d80b2"),      // EnergyType_Attack
    QColor("#ffe56d"),      // EnergyType_Energy
    QColor("#ffffff")       // EnergyType_Resource
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphicsItemEnergyBeam
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GraphicsItemEnergyBeam::~GraphicsItemEnergyBeam() {

}

const GraphicsItemEnergyBeam* GraphicsItemEnergyBeam::fire(QGraphicsScene* scene, const QPointF& source, const QPointF& target, EnergyType type, int zOrder /* = 0 */, int duration /* = ANIMATION_DURATION */) {
    GraphicsItemEnergyBeam* energyBeam = new GraphicsItemEnergyBeam(scene, source, target, zOrder);

    if(energyBeam) {
        energyBeam->fire(type, duration);
    }

    return energyBeam;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GraphicsItemEnergyBeam::finished() {
    scene()->removeItem(this);
    deleteLater();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GraphicsItemEnergyBeam::GraphicsItemEnergyBeam(QGraphicsScene* scene, const QPointF& source, const QPointF& target, int zOrder /* = 0 */, QGraphicsItem* parent /* = nullptr */)
    : _super(QLineF(source, source), parent),
      _source(source),
      _target(target),
      _lineAnimator(this) {

    Q_ASSERT(scene != nullptr);

    setZValue(zOrder);
    scene->addItem(this);

    connect(&_lineAnimator, &QPropertyAnimation::finished, this, &GraphicsItemEnergyBeam::finished);
}

void GraphicsItemEnergyBeam::fire(EnergyType type /* = EnergyType_Heal */, int duration /* = ANIMATION_DURATION */) {
    QPen pen(_COLORS[type], LINE_WIDTH, Qt::SolidLine, Qt::RoundCap);

    setPen(pen);

    // FIXME: The GraphicsLineItem bounding rect will change as the line length
    // is animated so need to find a way to call prepareGeometryChange() during the animation

    _lineAnimator.setTargetObject(this);
    _lineAnimator.setPropertyName("line");
    _lineAnimator.setStartValue(QLineF(_source, _source));
    _lineAnimator.setKeyValueAt (0.5, QLineF(_source, _target));
    _lineAnimator.setEndValue(QLineF(_target, _target));
    _lineAnimator.setDuration(duration);

    _lineAnimator.start();
}

//Game.getObjectById('5c226e9dc7a8e50421aeffda').heal(Game.getObjectById('6d156164d0408e3'))

//{
//    "_id": "6d156164d0408e3",
//    "density": 3,
//    "mineralAmount": 62196.64066651028,
//    "mineralType": "H",
//    "room": "W8N3",
//    "type": "mineral",
//    "x": 9,
//    "y": 43
//}

