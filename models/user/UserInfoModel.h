/*
 * File: UserInfoModel.h
 * Created: 2018-12-9
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

#ifndef _USERINFOMODEL_H
#define _USERINFOMODEL_H

#include <QObject>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RestResponseUserInfo;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UserInfoModel
// Contains information about the current authenticated user
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UserInfoModel : public QObject {
    typedef QObject _super;

    Q_OBJECT

public:
    explicit UserInfoModel(QObject *parent = nullptr);
    virtual ~UserInfoModel();

    bool isEmpty() const                        { return _isEmpty; }

    const QString& id() const                   { return _id; }
    const QString& userName() const             { return _userName; }

public slots:
    void refresh(const RestResponseUserInfo& response);

private:
    bool _isEmpty;

    QString _id;
    QString _userName;

};

#endif // _USERINFOMODEL_H
