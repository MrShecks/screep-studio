/*
 * File: ConsoleWidget.cpp
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

#include "ConsoleWidget.h"
#include "ui_ConsoleWidget.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConsoleWidget()
// UI component to display console output and allow the user to execute console commands
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ConsoleWidget::ConsoleWidget(QWidget* parent /* = nullptr */)
    : _super(parent),
      _ui(new Ui::ConsoleWidget),
      _model(0) {

    _ui->setupUi(this);
}

ConsoleWidget::~ConsoleWidget() {
    delete _ui;
}

void ConsoleWidget::setModel(ConsoleModel* model) {

    if(_model != model) {
        if(_model) {
            disconnect(_model, &ConsoleModel::rowsInserted, this, &ConsoleWidget::_onModelRowsInserted);
            disconnect(_ui->commandEdit, &QLineEdit::returnPressed, this, &ConsoleWidget::_onReturnPressed);
            disconnect(_ui->pauseButton, &QToolButton::toggled, _model, &ConsoleModel::setPaused);
            disconnect(_ui->clearButton, &QToolButton::clicked, _model, &ConsoleModel::clear);
        }

        if(model) {
            connect(model, &ConsoleModel::rowsInserted, this, &ConsoleWidget::_onModelRowsInserted);
            connect(_ui->commandEdit, &QLineEdit::returnPressed, this, &ConsoleWidget::_onReturnPressed);
            connect(_ui->pauseButton, &QToolButton::toggled, model, &ConsoleModel::setPaused);
            connect(_ui->clearButton, &QToolButton::clicked, model, &ConsoleModel::clear);

            model->setPaused(_ui->pauseButton->isChecked());
        }

        _ui->listView->setModel(model);
        _model = model;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConsoleWidget::_onModelRowsInserted(const QModelIndex& parent, int first, int last) {

    //
    // Using a 0 ms timer to call QListView::scrollToBottom() from the event queue. As per the Qt QTimer
    // documentation (https://doc.qt.io/qt-5/qtimer.html#details) specifying 0 for the timeout is a special
    // case and a commonly used technique to perform work afer UI events have completed. Without this the
    // QGraphicsView can lag when the console QListView is auto-scrolled.
    //
    // "As a special case, a QTimer with a timeout of 0 will time out as soon as all the events in the
    // window system's event queue have been processed. This can be used to do heavy work while providing
    // a snappy user interface"
    //

    QTimer::singleShot(0, _ui->listView, &QListView::scrollToBottom);

    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
}

void ConsoleWidget::_onReturnPressed() {
    Q_ASSERT(_model != nullptr);
    const QString expression = _ui->commandEdit->text();

    if(!expression.isEmpty()) {
        _model->sendCommand(expression, "shard0");        // FIXME: Need to get shard name (from application?)
        _ui->commandEdit->clear();
    }
}
