/*
 * File: JSONTreeModel.h
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

#ifndef _JSONTREEMODEL_H
#define _JSONTREEMODEL_H

#include <QAbstractItemModel>
#include <QJsonDocument>
#include <QList>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JSONTreeModel
// Tree model representation of a JSON document
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class JSONTreeModel : public QAbstractItemModel {
    typedef QAbstractItemModel _super;

    Q_OBJECT

    class TreeItem;

    static const int COLUMN_COUNT = 2;

public:
    explicit JSONTreeModel(QObject* parent = nullptr);
    virtual ~JSONTreeModel();

    bool setJson(const QJsonDocument& json);
    bool setJson(const QJsonObject& json);

    void setHeader(int column, const QString& text);

    const QJsonDocument& json() const;

    //
    // QAbstractItemModel
    //

    QVariant data(const QModelIndex& index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QModelIndex parent(const QModelIndex& index) const Q_DECL_OVERRIDE;

    int rowCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex& parent = QModelIndex()) const Q_DECL_OVERRIDE;

private:
    TreeItem* _root;

    QString _header[COLUMN_COUNT];
    QJsonDocument _json;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// JSONTreeModel::TreeItem
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class JSONTreeModel::TreeItem {
    friend class JSONTreeModel;

public:
    virtual ~TreeItem();

    const QString& label() const                { return _label; }
    const QString& value() const                { return _value; }

    const TreeItem* parent() const              { return _parent; }
    const TreeItem* childAt(int index) const    { return _children[index]; }

    int childCount() const                      { return _children.size(); }

    int row() const;

    void appendChild(TreeItem* child);

private:
    typedef QList<TreeItem *> TTreeItemList;

    QString _label;
    QString _value;

    TreeItem* _parent;
    TTreeItemList _children;

    TreeItem(TreeItem* parent = nullptr);
    TreeItem(const QString& label, TreeItem* parent = nullptr);

    static TreeItem* fromJson(const QString& label, const QJsonValue& value, TreeItem* parent);
};

#endif // _JSONTREEMODEL_H
