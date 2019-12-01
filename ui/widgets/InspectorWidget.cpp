/*
 * File: InspectorWidget.cpp
 * Created: 2018-12-13
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

#include <QClipboard>

#include "InspectorWidget.h"
#include "ui_InspectorWidget.h"

#include "ui/scenes/room/RoomGraphicsScene.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif // QT_DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InspectorWidget()
// UI component to display the JSON properties for a game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

InspectorWidget::InspectorWidget(QWidget* parent /* = nullptr */)
    : _super(parent),
      _ui(new Ui::InspectorWidget),
      _model(this) {

    _ui->setupUi(this);

    _model.setHeader(0, tr("Key"));
    _model.setHeader(1, tr("Value"));

    _ui->treeView->setModel(&_model);

    connect(_ui->buttonExpand, &QToolButton::toggled, this, &InspectorWidget::_onToggleExpandCollapse);
    connect(_ui->buttonCopy, &QToolButton::clicked, this, &InspectorWidget::_onCopyClicked);
}

InspectorWidget::~InspectorWidget() {
    delete _ui;
}

void InspectorWidget::setSelectedItem(const RoomGraphicsItem& item) {
    resetToolButtons();

    _model.setJson(item.roomEntity().json());
    _ui->entityType->setText(item.roomEntity().type());

    if(_ui->buttonExpand->isChecked())
        _ui->treeView->expandAll();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InspectorWidget::_onToggleExpandCollapse(bool isChecked) {
    if(isChecked)
        _ui->treeView->expandAll();
    else
        _ui->treeView->collapseAll();
}

void InspectorWidget::_onCopyClicked() {
    QClipboard* clipboard = QApplication::clipboard();

    clipboard->setText(_model.json ().toJson (QJsonDocument::Indented));
#ifdef QT_DEBUG
    qDebug().noquote() << "JSON=" << _model.json ().toJson (QJsonDocument::Compact);
#endif // QT_DEBUG
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void InspectorWidget::resetToolButtons() {
    _ui->buttonExpand->setEnabled(true);
    _ui->buttonCopy->setEnabled(true);
}
