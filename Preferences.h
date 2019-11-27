/*
 * File: Preferences.h
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

#ifndef _PREFERENCES_H
#define _PREFERENCES_H

#include <QObject>
#include <QSettings>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class QMainWindow;
class QDockWidget;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Preferences
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Preferences : QObject {
    typedef QObject _super;

public:
    Preferences(const QString& companyName, const QString applicationName, QObject* parent = nullptr);
    virtual ~Preferences();

    bool showGrid() const;
    void setShowGrid(bool show);

    void saveWindowState(const QString& tag, const QMainWindow* window);
    void restoreWindowState(const QString& tag, QMainWindow* window);

private:
    QSettings _settings;
};

#endif // _PREFERENCES_H
