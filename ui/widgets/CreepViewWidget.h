/*
 * File: CreepViewWidget.h
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

#ifndef _CREEPVIEWWIDGET_H
#define _CREEPVIEWWIDGET_H

#include <QWidget>

#include "ui/scenes/room/renderers/CreepRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CreepViewWidget
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CreepViewWidget : public QWidget {
    typedef QWidget _super;

public:
    CreepViewWidget(QWidget* parent = nullptr);
    virtual ~CreepViewWidget();

    //
    // QWidget
    //

    void paintEvent(QPaintEvent* event);

private:
    CreepRenderer _creepRenderer;
};

#endif // _CREEPVIEWWIDGET_H
