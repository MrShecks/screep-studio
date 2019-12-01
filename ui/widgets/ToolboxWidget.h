/*
 * File: ToolboxWidget.h
 * Created: 2018-12-26
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

#ifndef _TOOLBOXWIDGET_H
#define _TOOLBOXWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Ui {
    class ToolboxWidget;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ToolboxWidget()
// UI component to display the user tool palette
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ToolboxWidget : public QWidget {
    typedef QWidget _super;

    friend class ToolboxItemDelegate;

    static const int TOOLBOX_IMAGE_WIDTH        = 64;
    static const int TOOLBOX_IMAGE_HEIGHT       = 64;

public:

    enum ToolType {
        ToolType_Selector                       = 0,
        ToolType_Extension,
        ToolType_Road,
        ToolType_Wall,
        ToolType_Rampart,
        ToolType_Tower,
        ToolType_Container,
        ToolType_Storage,
        ToolType_Link,
        ToolType_Extractor,
        ToolType_Lab,
        ToolType_Terminal,
        ToolType_Spawn,
        ToolType_Observer,
        ToolType_PowerSpawn,
        ToolType_Nuker,

        ToolType_Count
    };

    ToolboxWidget(QWidget* parent = nullptr);
    virtual ~ToolboxWidget();

private:
    class ToolboxItem;

    Ui::ToolboxWidget* _ui;

    ToolboxItem* addItem(ToolType type, const QString& title, const QString& description);

    QImage getImage(ToolType type, const QSize& size, QColor fillColor) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ToolboxItem
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ToolboxWidget::ToolboxItem : public QListWidgetItem {
    typedef QListWidgetItem _super;

public:
    enum ItemRole {
        ItemRoleDescription                 = Qt::UserRole,
        ItemRoleImage
    };

    ToolboxItem(ToolboxWidget::ToolType type, const QString& title, const QString& description, const QImage& image = QImage(), QListWidget* parent = nullptr);
    virtual ~ToolboxItem();

    //
    // QListWidgetItem
    //

    QVariant data(int role) const;

private:
    QString _description;
    QImage _image;
};

#endif // _TOOLBOXWIDGET_H
