/*
 * File: RoomGraphicsView.h
 * Created: 2018-12-11
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

#ifndef _ROOMGRAPHICSVIEW_H
#define _ROOMGRAPHICSVIEW_H

#include <QGraphicsView>

#include "RoomGraphicsScene.h"
#include "../../models/room/RoomModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define _DEBUG_GRAPHICS_VIEW        1
#define _DEBUG_PRINT_SCENE          _DEBUG_GRAPHICS_VIEW && 1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsView
// Custom QGraphicsView used to render and interact with the room scene (RoomGraphicsScene)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class RoomGraphicsView : public QGraphicsView {
    typedef QGraphicsView _super;

    Q_OBJECT

public:
    RoomGraphicsView(RoomModel::TSharedPtr roomModel, QWidget* parent = nullptr);
    virtual ~RoomGraphicsView();

    void open();
    void close();

    void setModel(RoomModel::TSharedPtr roomModel);

    //
    // QGraphicsView
    //

    void wheelEvent(QWheelEvent* event);
#if _DEBUG_PRINT_SCENE
    void keyReleaseEvent(QKeyEvent* event);
#endif // _DEBUG_PRINT_SCENE

signals:
    void itemSelected(const RoomGraphicsItem& item);

public slots:
    void showGrid(bool show);

private slots:
    void _onSelectionChanged();

private:
    RoomGraphicsScene _roomScene;
    RoomModel::TSharedPtr _roomModel;
};

#endif // _ROOMGRAPHICSVIEW_H
