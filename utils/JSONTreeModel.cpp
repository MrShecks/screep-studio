/*
 * File: JSONTreeModel.cpp
 * Created: 2018-12-13
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

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "JSONTreeModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JSONTreeModel
// Tree model representation of a JSON document
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JSONTreeModel::JSONTreeModel(QObject* parent /* = nullptr */)
    : _super(parent),
      _root(new TreeItem()) {

}

JSONTreeModel::~JSONTreeModel() {
    delete _root;
}

bool JSONTreeModel::setJson(const QJsonDocument& json) {
    bool result = false;

    if(!json.isNull()) {
        beginResetModel();
        delete _root;

        if(json.isObject ())
            _root = TreeItem::fromJson("<root>", json.object(), _root);
        else if(json.isArray())
            _root = TreeItem::fromJson("<root>", json.array(), _root);

        _json = json;
        endResetModel();
        result = true;
    }

    return result;
}

bool JSONTreeModel::setJson(const QJsonObject& json) {
    return setJson(QJsonDocument(json));
}

void JSONTreeModel::setHeader(int column, const QString& text) {
    if(column >= 0 && column < COLUMN_COUNT)
        _header[column] = text;
}

const QJsonDocument& JSONTreeModel::json() const {
    return _json;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QVariant JSONTreeModel::data(const QModelIndex& index, int role) const {
    QVariant data;

    if(index.isValid() && role == Qt::DisplayRole) {
        const TreeItem* item = static_cast<TreeItem *>(index.internalPointer ());
        Q_ASSERT(item != nullptr);
        Q_ASSERT(index.column() >= 0 && index.column() < COLUMN_COUNT);

        switch(index.column()) {
            case 0:     data = item->label();                   break;
            case 1:     data = item->value();                   break;
            default:    data = QStringLiteral("<unknown>");     break;
        }
    }

    return data;
}

QVariant JSONTreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    QVariant data;

    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        Q_ASSERT(section >= 0 && section < COLUMN_COUNT);

        if(section >= 0 && section < COLUMN_COUNT)
            data = _header[section];
    }

    return data;
}

QModelIndex JSONTreeModel::index(int row, int column, const QModelIndex& parent /* = QModelIndex() */) const {
    QModelIndex itemIndex;

    if(hasIndex(row, column, parent)) {
        const TreeItem* parentItem;
        const TreeItem* childItem;

        if(!parent.isValid())
            parentItem = _root;
        else
            parentItem = static_cast<TreeItem *>(parent.internalPointer());

        if((childItem = parentItem->childAt (row)) != nullptr)
            itemIndex = createIndex(row, column, const_cast<TreeItem *>(childItem));
    }

    return itemIndex;
}

QModelIndex JSONTreeModel::parent(const QModelIndex& index) const {
    QModelIndex parentIndex;

    if(index.isValid()) {
        const TreeItem* childItem = static_cast<TreeItem *>(index.internalPointer());
        const TreeItem* parentItem = childItem->parent();

        if(parentItem != _root)
            parentIndex = createIndex(parentItem->row(), 0, const_cast<TreeItem *>(parentItem));
    }

    return parentIndex;
}

int JSONTreeModel::rowCount(const QModelIndex& parent /* = QModelIndex() */) const {
    int count = 0;

    if(parent.column() <= 0) {
        const TreeItem* parentItem;

        if(!parent.isValid())
            parentItem = _root;
        else
            parentItem = static_cast<TreeItem *>(parent.internalPointer());

        count = parentItem->childCount();
    }

    return count;
}

int JSONTreeModel::columnCount(const QModelIndex& parent /* = QModelIndex() */) const {
    Q_UNUSED(parent);

    return COLUMN_COUNT;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JSONTreeModel::TreeItem
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JSONTreeModel::TreeItem::~TreeItem() {
    qDeleteAll(_children);
}

int JSONTreeModel::TreeItem::row() const {
    return _parent != nullptr ? _parent->_children.indexOf(const_cast<TreeItem *>(this)) : 0;
}

void JSONTreeModel::TreeItem::appendChild(TreeItem* child) {
    _children.append(child);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JSONTreeModel::TreeItem::TreeItem(TreeItem* parent /* = nullptr */)
    : _parent(parent) {

}

JSONTreeModel::TreeItem::TreeItem(const QString& label, TreeItem* parent /* = nullptr */)
    : _label(label),
      _parent(parent) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

JSONTreeModel::TreeItem* JSONTreeModel::TreeItem::fromJson(const QString& label, const QJsonValue& value, TreeItem* parent) {
    TreeItem* item = new TreeItem(value.isArray () ? QString("%1[]").arg(label) : label, parent);

    if(value.isObject()) {
        const QJsonObject& json = value.toObject();
        QJsonObject::const_iterator it = json.constBegin();
        QJsonObject::const_iterator limit = json.constEnd();

        for(; it != limit; ++it) {
            TreeItem* child = TreeItem::fromJson(it.key(), it.value(), item);

            item->appendChild (child);
        }

    } else if(value.isArray()) {
        const QJsonArray& json = value.toArray();
        QJsonArray::const_iterator it = json.constBegin();
        QJsonArray::const_iterator limit = json.constEnd();

        for(int index = 0; it != limit; ++it, ++index) {
            const QString key = QString("[%1]").arg(index);
            TreeItem* child = TreeItem::fromJson(key, *it, item);

            item->appendChild(child);
        }

    } else {

        switch(value.type ()) {
            case QJsonValue::Double:    item->_value = QString::number(static_cast<qlonglong>(value.toDouble()));   break;
            default:                    item->_value = value.toVariant().toString();                                break;
        }
    }

    return item;
}
