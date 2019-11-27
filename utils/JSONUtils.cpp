/*
 * File: JSONUtils.cpp
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

#include "JSONUtils.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif // QT_DEBUG

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JsonUtils
// Utility class containing a collection of helper methods for manipulating JSON object
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int JSONUtils::getInt(const QJsonObject& json, const QString& key, int defaultValue /* = 0 */) {
    return json.contains(key) ? json[key].toInt(defaultValue) : defaultValue;
}

bool JSONUtils::getBool(const QJsonObject& json, const QString& key, bool defaultValue /* = false */) {
    return json.contains(key) ? json[key].toBool(defaultValue) : defaultValue;
}

double JSONUtils::getDouble(const QJsonObject& json, const QString& key, double defaultValue /* = 0 */) {
    return json.contains(key) ? json[key].toDouble(defaultValue) : defaultValue;
}

QString JSONUtils::getString(const QJsonObject& json, const QString& key, const QString& defaultValue /* = QString() */) {
    return json.contains(key) ? json[key].toString(defaultValue) : defaultValue;
}

bool JSONUtils::hasObject(const QJsonObject& json, const QString& key) {
    return json.contains(key) && json[key].isObject();
}

bool JSONUtils::hasArray(const QJsonObject& json, const QString& key) {
    return json.contains(key) && json[key].isArray();
}

QJsonObject JSONUtils::getObject(const QJsonObject& json, const QString& key) {
    return hasObject(json, key) ? json[key].toObject() : QJsonObject();
}

QJsonArray JSONUtils::getArray(const QJsonObject& json, const QString& key) {
    return hasArray(json, key) ? json[key].toArray() : QJsonArray();
}

QStringList JSONUtils::toStringList(const QJsonArray& json) {
    QJsonArray::const_iterator it = json.constBegin();
    QJsonArray::const_iterator limit = json.constEnd();
    QStringList list;

    for(; it != limit; ++it) {
        if(!it->isObject() && !it->isArray())
            list.append (it->toString());
    }

    return list;
}

QMap<QString, QString> JSONUtils::toStringMap(const QJsonObject& json) {
    QJsonObject::const_iterator it = json.constBegin();
    QJsonObject::const_iterator limit = json.constEnd();
    QMap<QString, QString> map;

    for(; it != limit; ++it) {
        if(!it.value().isObject() && !it.value().isArray()) {
            map.insert(it.key(), it.value ().toString());
        }
    }

    return map;
}

QJsonObject JSONUtils::mergeObjects(const QJsonObject& dest, const QJsonObject& src, MergeOptions options /* = MergeOption_None */) {
    QJsonObject::const_iterator it = src.constBegin();
    QJsonObject::const_iterator limit = src.constEnd();
    QJsonObject result = dest;

    for(; it != limit; ++it) {
        if(dest.contains(it.key())) {
            if(it.value().isObject())
                result.insert(it.key(), mergeObjects(dest[it.key()].toObject(), src[it.key()].toObject()));
            else if(it.value().isArray()) {
                if(!(options & MergeOption_IgnoreArrays))
                    result.insert(it.key(), mergeArrays(dest[it.key()].toArray(), src[it.key ()].toArray()));
#ifdef QT_DEBUG
                else {
                    qDebug() << "Warning: Ingoring array [" << it.key() << "]";
                }
#endif // QT_DEBUG
            } else {
                result.insert(it.key(), it.value());
            }
        } else {
            result.insert(it.key(), it.value());
        }
    }

    return result;
}

QJsonArray JSONUtils::mergeArrays(const QJsonArray& dest, const QJsonArray& src, MergeOptions options /* = MergeOption_None */) {
    QJsonArray::const_iterator it = src.constBegin();
    QJsonArray::const_iterator limit = src.constEnd();
    QJsonArray result = dest;

    for(; it != limit; ++it) {
        if(dest.contains(*it)) {
            if(it->isObject())
                Q_UNIMPLEMENTED();      // FIXME: How do I handle this? Is it even required?
            else if(it->isArray())
                Q_UNIMPLEMENTED();      // FIXME: How do I handle this? Is it even required?
        } else {
            result.append(*it);
        }
    }

    Q_UNUSED(options);

    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JSONUtils::JSONUtils() {

    //
    // Utility class can't be instanciated.
    //
}

