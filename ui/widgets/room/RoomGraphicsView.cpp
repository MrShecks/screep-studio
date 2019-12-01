/*
 * File: RoomGraphicsView.cpp
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

#include <QVBoxLayout>

#include "RoomGraphicsView.h"
#include "RoomGraphicsScene.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoomGraphicsView
// Custom QGraphicsView used to render and interact with the room scene (RoomGraphicsScene)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsView::RoomGraphicsView(RoomModel::TSharedPtr roomModel, QWidget* parent /* = nullptr */)
    : _super(parent),
      _roomScene(this),
      _roomModel(roomModel) {

    setScene(&_roomScene);
    setRenderHint(QPainter::Antialiasing, true);
    setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(DragMode::ScrollHandDrag);
    setCacheMode(QGraphicsView::CacheBackground);

    connect(&_roomScene, &RoomGraphicsScene::selectionChanged, this, &RoomGraphicsView::_onSelectionChanged);

    _roomScene.setModel (_roomModel);
}

RoomGraphicsView::~RoomGraphicsView() {

}

void RoomGraphicsView::open() {
    if(_roomModel)
        _roomModel->open();
}

void RoomGraphicsView::close() {
    if(_roomModel && _roomModel->isOpen())
        _roomModel->close();
}

void RoomGraphicsView::setModel(RoomModel::TSharedPtr roomModel) {
    _roomScene.setModel (roomModel);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomGraphicsView::showGrid(bool show) {
    _roomScene.showGrid(show);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomGraphicsView::_onSelectionChanged() {
    QList<QGraphicsItem *> selectedItems = _roomScene.selectedItems();

    if(!selectedItems.isEmpty()) {
        const RoomGraphicsItem* item = static_cast<RoomGraphicsItem *>(selectedItems[0]);
        Q_ASSERT(item != nullptr);

        emit itemSelected(*item);
    }

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RoomGraphicsView::wheelEvent(QWheelEvent* event) {

    // TODO: Add suport for upper and lower scale bounds

    if(event->modifiers() & Qt::ControlModifier || event->buttons() & Qt::LeftButton) {
        const ViewportAnchor anchor = transformationAnchor();
        int angle = event->angleDelta().y();
        qreal scaleFactor = angle > 0 ? 1.1f : 0.9f;

        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        scale(scaleFactor, scaleFactor);
        setTransformationAnchor (anchor);

    } else
        _super::wheelEvent(event);

}

#if _DEBUG_PRINT_SCENE
void RoomGraphicsView::keyReleaseEvent(QKeyEvent* event) {

    if(event->key() != Qt::Key_Pause)
        _super::keyReleaseEvent(event);
    else {
        QGraphicsScene* currentScene;

        if(!_roomModel.isNull() && (currentScene = scene()) != nullptr) {
            QImage image(currentScene->sceneRect().size().toSize(), QImage::Format_RGB32);
            QPainter painter(&image);

            painter.setRenderHint(QPainter::Antialiasing);
            currentScene->render(&painter);

            QString fileName = QString("Room-%1.png").arg(_roomModel->roomName());
            image.save(fileName);
        }
    }
}
#endif // _DEBUG_PRINT_SCENE

