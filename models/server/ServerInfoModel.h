/*
 * File: ServerInfoModel.h
 * Created: 2018-12-5
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

#ifndef _SERVERINFOMODEL_H
#define _SERVERINFOMODEL_H

#include <QObject>

#include "network/rest/RestServerInfo.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ServerInfoModel
// Information about the Screeps game server
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ServerInfoModel : public QObject {
    typedef QObject _super;

    Q_OBJECT

public:
    explicit ServerInfoModel(QObject* parent = nullptr);
    virtual ~ServerInfoModel();

    bool isEmpty() const                        { return _isEmpty; }

    int protocol() const                        { return _protocol; }
    const QString& packageVersion() const       { return _packageVersion; }
    const QString& welcomeMessage() const       { return _welcomeMessage; }

    bool hasShards() const                      { return !_shards.isEmpty(); }
    const QStringList& shards() const           { return _shards; }

public slots:
    void refresh(const RestResponseServerInfo& response);

private:
    bool _isEmpty;

    int _protocol;
    QString _packageVersion;
    QString _welcomeMessage;

    QStringList _shards;
};

#endif // _SERVERINFOMODEL_H
