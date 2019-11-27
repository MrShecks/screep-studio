/*
 * File: PropertiesWidget.h
 * Created: 2018-12-3
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

#ifndef PROPERTIESWIDGET_H
#define PROPERTIESWIDGET_H

#include <QWidget>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Ui {
    class PropertiesWidget;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PropertiesWidget()
// UI component to display the properties of selected game entities
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PropertiesWidget : public QWidget {
    typedef QWidget _super;

public:
    PropertiesWidget(QWidget* parent = nullptr);
    virtual ~PropertiesWidget();

private:
    Ui::PropertiesWidget* _ui;
};

#endif // PROPERTIESWIDGET_H
