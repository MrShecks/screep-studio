/*
 * File: ScreepStudioApplication.h
 * Created: 2018-12-2
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

#ifndef _SCREEPSTUDIOAPPLICATION_H
#define _SCREEPSTUDIOAPPLICATION_H

#include <QApplication>
#include <QMap>

#include "Preferences.h"

#include "models/client/ClientModel.h"

#include "models/NetworkModel.h"
#include "models/room/RoomModel.h"
#include "models/world/WorldModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ServerInfoModel;
class UserInfoModel;
class ConsoleModel;

class MainWindow;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ScreepStudioApplication()
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ScreepStudioApplication : public QApplication {
    typedef QApplication _super;

    Q_OBJECT

    const static QString COMPANY_NAME;
    const static QString APPLICATION_NAME;

public:
    ScreepStudioApplication(int& argc, char** argv, int flags = ApplicationFlags);
    virtual ~ScreepStudioApplication();

    Preferences& prefs()                        { return _prefs; }

    ServerInfoModel* serverInfoModel() const    { return _serverInfoModel; }
    UserInfoModel* userInfoModel() const        { return _userInfoModel; }
    ConsoleModel* consoleModel() const          { return _consoleModel; }

    const QString& userId() const;

    RoomModel::TSharedPtr createRoomModel(const QString& roomName, const QString& shardName = QString());
    void destroyRoomModel(const RoomModel::TSharedPtr roomModel);

private slots:
    void _onRoomTerrainReceived(const RestResponseRoomTerrain& response);
    void _onRoomEventReceived(const SocketEventRoom& event);
    void _onConnectionStateChanged(NetworkModel::ConnectionState oldState, NetworkModel::ConnectionState newState);

private:
    typedef QMap<QString, RoomModel::TSharedPtr> TRoomModelMap;

    Preferences _prefs;

    ClientModel* _clientModel;

    NetworkModel* _networkModel;

    ServerInfoModel* _serverInfoModel;
    UserInfoModel* _userInfoModel;
    WorldModel* _worldModel;
    ConsoleModel* _consoleModel;

    TRoomModelMap _roomModels;

    MainWindow* _mainWindow;

    RoomModel::TSharedPtr findRoomModel(const QString& roomName, const QString& shardName) const;
    RoomModel::TSharedPtr findRoomModel(const QString& mapKey) const;

    QString roomMapKey(const QString& roomName, const QString& shardName) const;
};

#endif // _SCREEPSTUDIOAPPLICATION_H
