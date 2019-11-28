/*
 * File: MainWindow.h
 * Created: 2018-11-24
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "./models/room/RoomModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace Ui {
    class MainWindow;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ScreepStudioApplication;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MainWindow
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow {
    typedef QMainWindow _super;

    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent* event);

public slots:
    void openRoom(const QString& roomName, const QString& shardName = QString());

    void unimplementedAction();
    void showAboutMessage();

private:
    Ui::MainWindow* _ui;

    ScreepStudioApplication* application() const;

    void addDockWidgetMenuItem(QMenu* menu, const QDockWidget* dockWidget, QKeySequence shortcut, const QString& icon);
};

#endif // MAINWINDOW_H
