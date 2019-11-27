/*
 * File: GraphicsItemLaserBeam.h
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

#ifndef _GRAPHICSITEMENERGYBEAM_H
#define _GRAPHICSITEMENERGYBEAM_H

#include <QGraphicsLineItem>
#include <QPropertyAnimation>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphicsItemEnergyBeam
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class GraphicsItemEnergyBeam : public QObject, public QGraphicsLineItem {
    typedef QGraphicsLineItem _super;

    Q_OBJECT
    Q_PROPERTY(QLineF line READ line WRITE setLine)

    static const int ANIMATION_DURATION         = 500;
    static const int LINE_WIDTH                 = 10;

public:

    enum EnergyType {
        EnergyType_Heal,
        EnergyType_Repair,
        EnergyType_Attack,
        EnergyType_Energy,
        EnergyType_Resource,

        EnergyType_Count
    };


    virtual ~GraphicsItemEnergyBeam();

    static const GraphicsItemEnergyBeam* fire(QGraphicsScene* scene, const QPointF& source, const QPointF& target, EnergyType type, int zOrder = 0, int duration = ANIMATION_DURATION);

private slots:
    void finished();

private:
    EnergyType _type;

    QPointF _source;
    QPointF _target;

    QPropertyAnimation _lineAnimator;

    static const QColor _COLORS[EnergyType_Count];

    GraphicsItemEnergyBeam(QGraphicsScene* scene, const QPointF& source, const QPointF& target, int zOrder = 0, QGraphicsItem* parent = nullptr);
    void fire(EnergyType type = EnergyType_Heal, int duration = ANIMATION_DURATION);
};

#endif // _GRAPHICSITEMENERGYBEAM_H
