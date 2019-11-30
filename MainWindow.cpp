/*
 * File: MainWindow.cpp
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

#include <QDockWidget>
#include <QMessageBox>
#include <QtDebug>

#include "MainWindow.h"
#include "ScreepStudioApplication.h"

#include "./widgets/PropertiesWidget.h"
#include "./widgets/InvasionWidget.h"
#include "./widgets/ConsoleWidget.h"
#include "./widgets/room/RoomGraphicsView.h"

#include "ui_MainWindow.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MainWindow
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget* parent /* = nullptr */)
    : QMainWindow(parent),
      _ui(new Ui::MainWindow) {

    _ui->setupUi(this);
    _ui->consoleWidget->setModel(application()->consoleModel());

    addDockWidgetMenuItem(_ui->menuWindow, _ui->toolBoxDockWidget, QKeySequence(Qt::CTRL + Qt::Key_T), ":/assets/images/toolbox.svg");
    addDockWidgetMenuItem(_ui->menuWindow, _ui->invasionDockWidget, QKeySequence(Qt::CTRL + Qt::Key_N), ":/assets/images/invader.svg");
    addDockWidgetMenuItem(_ui->menuWindow, _ui->propertiesDockWidget, QKeySequence(Qt::CTRL + Qt::Key_P), ":/assets/images/properties.svg");
    addDockWidgetMenuItem(_ui->menuWindow, _ui->inspectorDockWidget, QKeySequence(Qt::CTRL + Qt::Key_I), ":/assets/images/object.svg");
    addDockWidgetMenuItem(_ui->menuWindow, _ui->consoleDockWidget, QKeySequence(Qt::CTRL + Qt::Key_C), ":/assets/images/console.svg");

    connect(_ui->actionOpen, &QAction::triggered, this, &MainWindow::unimplementedAction);
    connect(_ui->actionZoomIn, &QAction::triggered, this, &MainWindow::unimplementedAction);
    connect(_ui->actionZoomOut, &QAction::triggered, this, &MainWindow::unimplementedAction);

    connect(_ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutMessage);
    connect(_ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    Preferences& prefs = application()->prefs();

    prefs.restoreWindowState("MainWindow", this);
    _ui->actionShowGrid->setChecked(prefs.showGrid());
}

MainWindow::~MainWindow() {
    delete _ui;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::openRoom(const QString& roomName, const QString& shardName /* = QString() */) {
    RoomModel::TSharedPtr roomModel;

    if((roomModel = application()->createRoomModel(roomName, shardName)) != nullptr) {
        RoomGraphicsView* roomGraphicsView = new RoomGraphicsView(roomModel, this);
        QWidget* widget = new QWidget();
        QLayout* layout = new QVBoxLayout(widget);

        // FIXME: There's a memory leak here but this needs to be re-written anyway so it will be fixed then :)

        layout->addWidget (roomGraphicsView);

        _ui->tabWidget->addTab(widget, QIcon(":/assets/images/object.svg"), roomModel->roomName());

        connect(roomGraphicsView, &RoomGraphicsView::itemSelected, _ui->inspectorWidget, &InspectorWidget::setSelectedItem);
        connect(_ui->actionShowGrid, &QAction::triggered, roomGraphicsView, &RoomGraphicsView::showGrid);

        roomGraphicsView->showGrid(_ui->actionShowGrid->isChecked());
        roomGraphicsView->open();
    }
}

void MainWindow::unimplementedAction() {
    QMessageBox::information (this, tr("Unimplemented Function"), tr("FIXME: This functionality has not been implemented."));
}

void MainWindow::showAboutMessage() {
    QMessageBox::about(this,tr("About"),
        QString(tr("%1\n%2 (shecks@gmail.com)\n\nNote: This application is in development and not feature complete."))
                       .arg(application()->applicationName())
                       .arg(application()->organizationName()));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::closeEvent(QCloseEvent* event) {
#ifndef QT_DEBUG
    int result = QMessageBox::question (this, tr("Exit Application"), tr("Are you sure you want to exit the application?"), QMessageBox::Yes|QMessageBox::No);
#else
    int result = QMessageBox::Yes;
#endif // QT_DEBUG

    switch(result) {
        case QMessageBox::Yes: {
            for(int index = 0; index < _ui->tabWidget->count(); ++index) {
                QWidget* child = _ui->tabWidget->widget(index);
                QLayoutItem* layoutItem = child->layout()->takeAt(0);
                RoomGraphicsView* roomGraphicsView = static_cast<RoomGraphicsView *>(layoutItem->widget ());
                Q_ASSERT(roomGraphicsView != nullptr);

                roomGraphicsView->close();
            }

            Preferences& prefs = application()->prefs();

            prefs.setShowGrid(_ui->actionShowGrid->isChecked());
            prefs.saveWindowState("MainWindow", this);

            event->accept();
        }
        break;

        default: {
            event->ignore();
        }
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ScreepStudioApplication* MainWindow::application() const {
    return qobject_cast<ScreepStudioApplication *>(QApplication::instance ());
}

void MainWindow::addDockWidgetMenuItem(QMenu* menu, const QDockWidget* dockWidget, QKeySequence shortcut, const QString& icon) {
    QAction* action = dockWidget->toggleViewAction();

    action->setShortcut(shortcut);
    action->setIcon(QIcon(icon));
    menu->addAction(action);
}

