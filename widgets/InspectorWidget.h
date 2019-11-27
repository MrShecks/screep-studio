/*
 * File: InspectorWidget.h
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

#ifndef INSPECTORWIDGET_H
#define INSPECTORWIDGET_H

#include <QWidget>

#include "../widgets/room/entities/RoomGraphicsItem.h"
#include "./utils/JSONTreeModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Ui {
    class InspectorWidget;
}

//template<class T> class RoomGraphicsItem;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InspectorWidget()
// UI component to display the JSON properties for a game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class InspectorWidget : public QWidget {
    typedef QWidget _super;

    Q_OBJECT

public:
    explicit InspectorWidget(QWidget* parent = nullptr);
    virtual ~InspectorWidget();

public slots:
    void setSelectedItem(const RoomGraphicsItem& item);

private slots:
    void _onToggleExpandCollapse(bool isChecked);
    void _onCopyClicked();

private:
    Ui::InspectorWidget* _ui;

    JSONTreeModel _model;

    void resetToolButtons();
};

#endif // INSPECTORWIDGET_H
