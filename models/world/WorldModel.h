/*
 * File: WorldModel.h
 * Created: 2019-1-28
 *
 * Copyright (c) shecks 2019 <shecks@gmail.com>
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

#ifndef _WORLDMODEL_H
#define _WORLDMODEL_H

#include <QObject>
#include <QPointer>
#include <QString>

#include "../NetworkModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WorldModel()
// Representation of a world shard
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class WorldModel : public QObject {
    typedef QObject _super;

    Q_OBJECT

public:
    typedef QSharedPointer<WorldModel> TSharedPtr;

    explicit WorldModel(NetworkModel* networkModelQ, QObject* parent = nullptr);
    virtual ~WorldModel();

    void open(const QString& shardName = QString());
    void close();

    bool isOpen() const;

signals:
    void opened(const QString& shardName);
    void closed(const QString& shardName);

public slots:
    void _onWorldSizeReceived(const WorldSizeResponse& response);

private:
    QPointer<NetworkModel> _networkModel;

    QString _shardName;
};

#endif // _WORLDMODEL_H
