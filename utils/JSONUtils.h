/*
 * File: JSONUtils.h
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

#ifndef _JSONUTILS_H
#define _JSONUTILS_H

#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QMap>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JsonUtils
// Utility class containing a collection of helper methods for manipulating JSON object
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class JSONUtils {

public:
    static int getInt(const QJsonObject& json, const QString& key, int defaultValue = 0);
    static bool getBool(const QJsonObject& json, const QString& key, bool defaultValue = false);
    static double getDouble(const QJsonObject& json, const QString& key, double defaultValue = 0);
    static QString getString(const QJsonObject& json, const QString& key, const QString& defaultValue = QString());

    static QJsonObject getObject(const QJsonObject& json, const QString& key);
    static QJsonArray getArray(const QJsonObject& json, const QString& key);

    static bool hasObject(const QJsonObject& json, const QString& key);
    static bool hasArray(const QJsonObject& json, const QString& key);

    static QStringList toStringList(const QJsonArray& json);
    static QMap<QString, QString> toStringMap(const QJsonObject& json);

    enum MergeOptions {
        MergeOption_None            = 0x00,
        MergeOption_IgnoreArrays    = 0x01
    };

    static QJsonObject mergeObjects(const QJsonObject& dest, const QJsonObject& src, MergeOptions options = MergeOption_None);
    static QJsonArray mergeArrays(const QJsonArray& dest, const QJsonArray& src, MergeOptions options = MergeOption_None);

private:
    JSONUtils();
};

#endif // JSONUTILS_H
