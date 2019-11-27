/*
 * File: Preferences.cpp
 * Created: 2018-12-12
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

#include <QMainWindow>
#include <QDockWidget>

#include "Preferences.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Preferences
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Preferences::Preferences(const QString& companyName, const QString applicationName, QObject* parent /* = nullptr */)
    : _super(parent),
      _settings(companyName, applicationName) {

}

Preferences::~Preferences() {

}

bool Preferences::showGrid() const {
    return _settings.value("Settings/showGrid", false).toBool();
}

void Preferences::setShowGrid(bool show) {
    _settings.setValue("Settings/showGrid", show);
}

void Preferences::saveWindowState(const QString& tag, const QMainWindow* window) {
    _settings.setValue(QString("%1/geometry").arg(tag), window->saveGeometry());
    _settings.setValue(QString("%1/windowState").arg(tag), window->saveState());
}

void Preferences::restoreWindowState(const QString& tag, QMainWindow* window) {
    window->restoreState(_settings.value(QString("%1/windowState").arg(tag)).toByteArray());
    window->restoreGeometry(_settings.value(QString("%1/geometry").arg(tag)).toByteArray());
}
