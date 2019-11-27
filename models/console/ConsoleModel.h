/*
 * File: ConsoleModel.h
 * Created: 2018-12-8
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

#ifndef _CONSOLEMODEL_H
#define _CONSOLEMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QTime>

#include "../../ScreepsApi.h"
#include "../../network/SocketNetworkManager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NetworkModel;
class SocketEventConsole;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConsoleModel
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Item {
    friend class ConsoleModel;

public:
    enum ItemType {
        LogMessage,
        UserCommand,
        CommandResult,
        ErrorMessage
    };

    ItemType type() const                       { return _type; }
    const QString& text() const                 { return _text; }
    const QTime& timeStamp() const              { return _timeStamp; }

    Screeps::Result resultCode() const {
        Q_ASSERT(_type == CommandResult);
        return _type == CommandResult
                ? static_cast<Screeps::Result>(_text.toInt())
                : Screeps::ERR_OK;
    }

private:
    ItemType _type;
    QString _text;
    QTime _timeStamp;

    Item(ItemType type, const QString& text)
        : _type(type), _text(text), _timeStamp(QTime::currentTime()) {

    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ConsoleModel : public QAbstractListModel {
    typedef QAbstractListModel _super;

    Q_OBJECT

    static const int MAX_CONSOLE_ITEMS = 100;

    static const QColor COLOR_LOG_MESSAGE;
    static const QColor COLOR_USER_COMMAND;
    static const QColor COLOR_COMMAND_RESULT;
    static const QColor COLOR_ERROR_MESSAGE;

public:
    typedef QSharedPointer<ConsoleModel> TSharedPtr;

    ConsoleModel(QObject* parent = nullptr);
    virtual ~ConsoleModel();

    bool isPaused() const                       { return _isPaused; }

    void setModel(NetworkModel* model);

    //
    // QAbstractItemModel
    //

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;

public slots:
    void setPaused(bool isPaused);
    void clear();

    void sendCommand(const QString& expression, const QString& shardName);

private slots:
    void _onConsoleEventReceived(const SocketEventConsole& event);

private:
    typedef QHash<Screeps::Result, QString> TResultMap;
    typedef QList<Item> TItemList;

    NetworkModel* _model;

    TItemList _items;
    bool _isPaused;

    static const TResultMap _RESULT_MAP;

    void addItems(const TItemList& items);

    QString decodeString(const QString& encoded) const;
};

#endif // _CONSOLEMODEL_H
