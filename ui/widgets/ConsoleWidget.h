/*
 * File: ConsoleWidget.h
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

#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>

#include "models/console/ConsoleModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Ui {
    class ConsoleWidget;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConsoleWidget()
// UI component to display console output and allow the user to execute console commands
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ConsoleWidget : public QWidget {
    typedef QWidget _super;

    Q_OBJECT

public:
    ConsoleWidget(QWidget* parent = nullptr);
    virtual ~ConsoleWidget();

    void setModel(ConsoleModel* model);

private slots:
    void _onModelRowsInserted(const QModelIndex& parent, int first, int last);
    void _onReturnPressed();

private:
    Ui::ConsoleWidget* _ui;
    ConsoleModel* _model;
};

#endif // CONSOLEWIDGET_H
