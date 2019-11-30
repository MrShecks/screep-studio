/*
 * File: ConsoleModel.cpp
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

#include <QBrush>

#include "ConsoleModel.h"
#include "../NetworkModel.h"
#include "../../utils/JSONUtils.h"
#include "../../network/socket/SocketEventConsole.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor ConsoleModel::COLOR_LOG_MESSAGE        = QColor(Qt::gray);
const QColor ConsoleModel::COLOR_USER_COMMAND       = QColor("#7986cb");
const QColor ConsoleModel::COLOR_COMMAND_RESULT     = QColor(Qt::cyan);
const QColor ConsoleModel::COLOR_ERROR_MESSAGE      = QColor(Qt::red);

const ConsoleModel::TResultMap ConsoleModel::_RESULT_MAP = {
    { Screeps::ERR_OK,                  QStringLiteral("OK") },
    { Screeps::ERR_NOT_OWNER,           QStringLiteral("ERR_NOT_OWNER") },
    { Screeps::ERR_NO_PATH,             QStringLiteral("ERR_NO_PATH") },
    { Screeps::ERR_NAME_EXISTS,         QStringLiteral("ERR_NAME_EXISTS") },
    { Screeps::ERR_BUSY,                QStringLiteral("ERR_BUSY") },
    { Screeps::ERR_NOT_FOUND,           QStringLiteral("ERR_NOT_FOUND") },
    { Screeps::ERR_NOT_ENOUGH_ENERGY,   QStringLiteral("ERR_NOT_ENOUGH_ENERGY") },
    { Screeps::ERR_INVALID_TARGET,      QStringLiteral("ERR_INVALID_TARGET") },
    { Screeps::ERR_FULL,                QStringLiteral("ERR_FULL") },
    { Screeps::ERR_NOT_IN_RANGE,        QStringLiteral("ERR_NOT_IN_RANGE") },
    { Screeps::ERR_INVALID_ARGS,        QStringLiteral("ERR_INVALID_ARGS") },
    { Screeps::ERR_TIRED,               QStringLiteral("ERR_TIRED") },
    { Screeps::ERR_NO_BODYPART,         QStringLiteral("ERR_NO_BODYPART") },
    { Screeps::ERR_RCL_NOT_ENOUGH,      QStringLiteral("ERR_RCL_NOT_ENOUGH") },
    { Screeps::ERR_GCL_NOT_ENOUGH,      QStringLiteral("ERR_GCL_NOT_ENOUGH") },
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ConsoleModel
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ConsoleModel::ConsoleModel(QObject* parent /* = nullptr */)
    : _super(parent),
      _model(0),
      _isPaused(false) {
}

ConsoleModel::~ConsoleModel() {
    _model = 0;
}

void ConsoleModel::setModel(NetworkModel* model) {
    if(_model != model) {
        if(_model) {
            disconnect(_model, &NetworkModel::consoleEventReceived, this, &ConsoleModel::_onConsoleEventReceived);
        }

        if(model) {
            connect(model, &NetworkModel::consoleEventReceived, this, &ConsoleModel::_onConsoleEventReceived);
        }

        _model = model;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ConsoleModel::rowCount(const QModelIndex& parent /* = QModelIndex() */) const {
    Q_UNUSED(parent);

    return _items.size();
}

QVariant ConsoleModel::data(const QModelIndex &index, int role /* = Qt::DisplayRole */) const {
    QVariant data;

    if(index.row() >= 0 && index.row() < _items.size() && index.column() == 0) {
        const Item& item = _items[index.row()];

        switch(role) {
            case Qt::DisplayRole: {
                switch(item.type()) {
                    case Item::UserCommand: {
                        data = QString("> %1").arg(item.text());
                    }
                    break;

                    case Item::CommandResult: {
                        QString resultCodeName = _RESULT_MAP.value(item.resultCode(), "ERR_UNKNOWN");

                        if(item.resultCode () != Screeps::ERR_OK)
                            resultCodeName += QString("(%1)").arg(item.resultCode());

                        data = QString("[%1] %2").arg(item.timeStamp().toString("HH:mm:ss")).arg(resultCodeName);
                    }
                    break;

                    default: {
                        data = QString("[%1] %2").arg(item.timeStamp().toString("HH:mm:ss")).arg(decodeString(item.text()));
                    }
                    break;
                }
            }
            break;

            case Qt::ForegroundRole: {
                switch(item.type()) {
                    case Item::LogMessage:          data = QBrush(COLOR_LOG_MESSAGE);       break;
                    case Item::UserCommand:         data = QBrush(COLOR_USER_COMMAND);      break;
                    case Item::CommandResult:       data = QBrush(COLOR_COMMAND_RESULT);    break;
                    case Item::ErrorMessage:        data = QBrush(COLOR_ERROR_MESSAGE);     break;
                }
            }
            break;
        }
    }

    return data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConsoleModel::setPaused(bool isPaused) {
    _isPaused = isPaused;
}

void ConsoleModel::clear() {
    beginResetModel();
    _items.clear();
    endResetModel();
}

void ConsoleModel::sendCommand(const QString& expression, const QString& shardName) {
    Q_ASSERT(_model != nullptr);

    // Test Commands
    // Game.rooms["W8N3"].createConstructionSite(21,22, 'storage')
    // JSON.stringify(Game.gcl)
    // JSON.stringify(Game.rooms)

    if(_model) {
        TItemList items;

        items.append(Item(Item::UserCommand, expression));
        addItems(items);

        _model->sendConsoleCommand(expression, shardName);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConsoleModel::_onConsoleEventReceived(const SocketEventConsole& event) {

    if(!_isPaused) {
        TItemList items;

        for(QString& logMessage : event.logMessages ())
            items.append(Item(Item::LogMessage, logMessage));

        for(QString commandResult : event.commandResults())
            items.append(Item(Item::CommandResult, commandResult));

        if(!event.errorMessage().isEmpty())
            items.append(Item(Item::ErrorMessage, event.errorMessage()));

        addItems(items);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ConsoleModel::addItems(const TItemList& items) {
    Q_ASSERT_X(!items.isEmpty(), "ConsoleModel::addItems", "addItems() called with empty array");

    //
    // TODO: Look into basing the model on QContiguousCache instead
    // of QList. A cache container would be more efficient but
    // QContiguousCache indices are not stable so some additional
    // work is required to map them to model indices
    //

    //
    // FIXME: The server shouldn't be sending an empty list, but just in case...
    //

    if(!items.isEmpty()) {
        int count = _items.count();

        beginInsertRows(QModelIndex(), count, count + items.count() - 1);
        _items.append(items);
        endInsertRows();

        if(_items.count() > MAX_CONSOLE_ITEMS) {
            int numRowsToRemove = _items.count() - MAX_CONSOLE_ITEMS;

            beginRemoveRows(QModelIndex(), 0, numRowsToRemove - 1);
            _items.erase(_items.begin(), _items.begin() + numRowsToRemove);
            endRemoveRows();
        }
    }
}

QString ConsoleModel::decodeString(const QString& encoded) const {
    static const QHash<QString, QString> tags = {
        { QStringLiteral("&amp;"),  QStringLiteral("&") },
        { QStringLiteral("&lt;"),   QStringLiteral("<") },
        { QStringLiteral("&gt;"),   QStringLiteral(">") },
    };

    QHash<QString, QString>::const_iterator it = tags.constBegin();
    QHash<QString, QString>::const_iterator limit = tags.constEnd();
    QString str = encoded;

    for(; it != limit; ++it)
        str.replace(it.key(), it.value ());

    return str;
}

