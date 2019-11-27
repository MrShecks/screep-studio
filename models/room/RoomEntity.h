/*
 * File: RoomEntity.h
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

#ifndef _ENTITY_H
#define _ENTITY_H

#include <QJsonObject>
#include <QPointF>

#include "ScreepsApi.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Entity
// A wrapper class around the JSON object used to represent a dynamic room entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomEntity {

    friend class RoomModel;
    friend class RoomEntityModel;

    static const QString _METADATA_KEY;

public:
    virtual ~RoomEntity();

    QString id() const                          { return getString("_id"); }
    QString type() const                        { return getString("type"); }
    QString room() const                        { return getString("room"); }

    int posX() const                            { return getInt("x"); }
    int posY() const                            { return getInt("y"); }

    int hits() const                            { return getInt("hits"); }
    int hitsMax() const                         { return getInt("hitsMax"); }

    QPoint pos() const                          { return QPoint(posX(), posY()); }

    Screeps::EntityType entityType() const;

    //
    // FIXME: These accessors should probably be protected but they are
    // handy to have access to while developing/debugging
    //
    // Note: Will need to do a bit of refactoring if these are may protected
    // as they are used by the RoomGraphicsItemsXXXX classes.
    //

    int getInt(const QString& key, int defaultValue = 0) const;
    bool getBool(const QString& key, bool defaultValue = false) const;
    double getDouble(const QString& key, double defaultValue = 0) const;
    QString getString(const QString& key, const QString& defaultValue = QString()) const;

    int getInt(const QJsonObject& json, const QString& key, int defaultValue = 0) const;
    bool getBool(const QJsonObject& json, const QString& key, bool defaultValue = false) const;
    double getDouble(const QJsonObject& json, const QString& key, double defaultValue = 0) const;
    QString getString(const QJsonObject& json, const QString& key, const QString& defaultValue = QString()) const;

    bool hasObject(const QString& key) const;
    bool hasArray(const QString& key) const;

    QJsonObject getObject(const QString& key) const;
    QJsonArray getArray(const QString& key) const;

    QJsonObject getMetaData() const;

    const QJsonObject& json() const;

    QString toString() const;

private:
    QJsonObject _json;

    RoomEntity(const QJsonObject& json);

    void applyUpdate(const QJsonObject& json);
    void setMetaData(const QJsonObject& data);
};

#endif // _ENTITY_H
