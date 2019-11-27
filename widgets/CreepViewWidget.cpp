/*
 * File: CreepViewWidget.cpp
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

#include "CreepViewWidget.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreepViewWidget
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CreepViewWidget::CreepViewWidget(QWidget* parent /* = nullptr */)
    : _super(parent),
      _creepRenderer(this) {

    _creepRenderer.addBodyPart (Screeps::BodyPart_Move, 10);
    _creepRenderer.setEnergy(300);
    _creepRenderer.setEnergyCapacity(600);

    _creepRenderer.setTough(true);
}

CreepViewWidget::~CreepViewWidget() {

}

void CreepViewWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QRect rc = rect();

    painter.fillRect(rc, QBrush(Qt::black));

    _creepRenderer.draw(&painter, rc);

    Q_UNUSED(event);
}
