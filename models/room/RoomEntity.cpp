/*
 * File: RoomEntity.cpp
 * Created: 2018-12-10
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

#include <QJsonDocument>

#include "RoomEntity.h"
#include "utils/JSONUtils.h"

#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString RoomEntity::_METADATA_KEY = QStringLiteral("$_meta_data");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Entity
// A wrapper class around the JSON object used to represent a dynamic room entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomEntity::~RoomEntity() {

}

Screeps::EntityType RoomEntity::entityType() const {
    return Screeps::getEntityType(type());
}

int RoomEntity::getInt(const QString& key, int defaultValue /* = 0 */) const {
    return getInt(_json, key, defaultValue);
}

bool RoomEntity::getBool(const QString& key, bool defaultValue /* = false */) const {
    return getBool(_json, key, defaultValue);
}

double RoomEntity::getDouble(const QString& key, double defaultValue /* = 0 */) const {
    return getDouble(_json, key, defaultValue);
}

QString RoomEntity::getString(const QString& key, const QString& defaultValue /* = QString() */) const {
    return getString(_json, key, defaultValue);
}

int RoomEntity::getInt(const QJsonObject& json, const QString& key, int defaultValue /* = 0 */) const {
    return JSONUtils::getInt(json, key, defaultValue);
}

bool RoomEntity::getBool(const QJsonObject& json, const QString& key, bool defaultValue /* = false */) const {
    return JSONUtils::getBool(json, key, defaultValue);
}

double RoomEntity::getDouble(const QJsonObject& json, const QString& key, double defaultValue /* = 0 */) const {
    return JSONUtils::getDouble(json, key, defaultValue);
}

QString RoomEntity::getString(const QJsonObject& json, const QString& key, const QString& defaultValue /* = QString() */) const {
    return JSONUtils::getString(json, key, defaultValue);
}

bool RoomEntity::hasObject(const QString& key) const {
    return JSONUtils::hasObject(_json, key);
}

bool RoomEntity::hasArray(const QString& key) const {
    return JSONUtils::hasArray(_json, key);
}

QJsonObject RoomEntity::getObject(const QString& key) const {
    return JSONUtils::getObject(_json, key);
}

QJsonArray RoomEntity::getArray(const QString& key) const {
    return JSONUtils::getArray(_json, key);
}

QJsonObject RoomEntity::getMetaData() const {
    return getObject(_METADATA_KEY);
}

const QJsonObject& RoomEntity::json() const {
    return _json;
}

QString RoomEntity::toString() const {
    const QJsonDocument document(_json);

    return document.toJson(QJsonDocument::Compact);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomEntity::RoomEntity(const QJsonObject& json)
    : _json(json) {
}

void RoomEntity::applyUpdate(const QJsonObject& json) {
    _json = JSONUtils::mergeObjects(_json, json, JSONUtils::MergeOption_IgnoreArrays);
}

void RoomEntity::setMetaData(const QJsonObject &data) {
    _json.insert(_METADATA_KEY, data);
}
