/*
 * File: SocketEventRoom.cpp
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

#include <QStringList>
#include <QRegularExpression>

#include "SocketEventRoom.h"
#include "utils/JSONUtils.h"

#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketEventRoom
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

SocketEventRoom::SocketEventRoom(const SocketResponse& response)
    : _super(response) {
    static const QRegularExpression REGEX_STREAM = QRegularExpression("((?<shard>\\w+)\\/)?(?<room>\\w+)");
    Q_ASSERT_X(REGEX_STREAM.match(response.stream()).hasMatch(), "SocketEventRoom::SocketEventRoom", "Unexpected room name format.");
    QRegularExpressionMatch match;

    // ((?<shard>\w+)\/)?(?<room>\w+)

    _gameTime = JSONUtils::getInt(json().object(), "gameTime", 0);

    if((match = REGEX_STREAM.match(response.stream())).hasMatch()) {
        _shardName = match.captured("shard");
        _roomName = match.captured("room");
    }

    if(JSONUtils::hasObject (json().object(), "objects")) {
        const QJsonObject objects = JSONUtils::getObject(json().object(), "objects");
        QJsonObject::const_iterator it = objects.constBegin();
        QJsonObject::const_iterator limit = objects.constEnd();

        for(; it != limit; ++it) {
            if(it.value().isNull()) {
                //
                // If the object map contains a key but no JSON object then it means
                // that the object was removed from the room since the last tick.
                // A removed entity is represented by RoomEntity() with an empty
                // JSON object
                //

                _entities.append(RoomEntity(it.key()));

            }
            else if(it.value().isObject ()) {

                //
                // When the server sends object updates, it only sends the attributes
                // that have changed since the last tick so all attributes in the JSON
                // object are optional, we can't rely on "_id" being present to use as
                // a unique object id later so we will explicitly store the map key as
                // part of the RoomEntity instead which is also the object id.
                //

                _entities.append(RoomEntity(it.key(), it.value().toObject()));
            }
        }
    }
}

SocketEventRoom::~SocketEventRoom() {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SocketEventRoom::RoomEntity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString& SocketEventRoom::RoomEntity::id() const {
    return _id;
}

const QJsonObject& SocketEventRoom::RoomEntity::json() const {
    return _json;
}

bool SocketEventRoom::RoomEntity::isRemoved() const {
    return _json.isEmpty();
}

QString SocketEventRoom::RoomEntity::type() const {
    return JSONUtils::getString(_json, "type");
}

SocketEventRoom::RoomEntity::RoomEntity(const QString& id, const QJsonObject& json /* = QJsonObject() */)
    : _id(id),
      _json(json) {

}
