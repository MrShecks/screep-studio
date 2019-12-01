/*
 * File: RoomGraphicsItem.cpp
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

#include <QPainter>
#include <QtMath>

#include "RoomGraphicsItem.h"
#include "RoomGraphicsItemWall.h"
#include "RoomGraphicsItemCreep.h"
#include "RoomGraphicsItemSpawn.h"
#include "RoomGraphicsItemTower.h"
#include "RoomGraphicsItemSource.h"
#include "RoomGraphicsItemMineral.h"
#include "RoomGraphicsItemExtractor.h"
#include "RoomGraphicsItemExtension.h"
#include "RoomGraphicsItemController.h"
#include "RoomGraphicsItemConstructionSite.h"
#include "RoomGraphicsItemTombstone.h"
#include "RoomGraphicsItemStorage.h"
#include "RoomGraphicsItemContainer.h"
#include "RoomGraphicsItemRoad.h"
#include "RoomGraphicsItemLink.h"
#include "RoomGraphicsItemEnergy.h"
#include "RoomGraphicsItemTerminal.h"
#include "RoomGraphicsItemLab.h"
#include "RoomGraphicsItemNuker.h"
#include "RoomGraphicsItemRampart.h"
#include "RoomGraphicsItemPowerSpawn.h"
#include "RoomGraphicsItemObserver.h"

#include "RoomGraphicsItemUnknown.h"
#include "ui/scenes/room/RoomGraphicsScene.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QColor RoomGraphicsItem::SELECTION_PEN_COLOR  = QColor("#5763a2");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GraphicsItemBase
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItem::~RoomGraphicsItem() {

}

RoomGraphicsItem* RoomGraphicsItem::create(const QString& type, const RoomEntity& entity, const QSize& cellSize) {
    RoomGraphicsItem* item = nullptr;

    // Poor mans factory ;)

    switch(Screeps::getEntityType(type)) {
        case Screeps::EntityType_Creep:                 item = new RoomGraphicsItemCreep(entity, cellSize);             break;
        case Screeps::EntityType_Spawn:                 item = new RoomGraphicsItemSpawn(entity, cellSize);             break;
        case Screeps::EntityType_Tower:                 item = new RoomGraphicsItemTower(entity, cellSize);             break;
        case Screeps::EntityType_Source:                item = new RoomGraphicsItemSource(entity, cellSize);            break;
        case Screeps::EntityType_Mineral:               item = new RoomGraphicsItemMineral(entity, cellSize);           break;
        case Screeps::EntityType_Extractor:             item = new RoomGraphicsItemExtractor(entity, cellSize);         break;
        case Screeps::EntityType_Extension:             item = new RoomGraphicsItemExtension(entity, cellSize);         break;
        case Screeps::EntityType_Controller:            item = new RoomGraphicsItemController(entity, cellSize);        break;
        case Screeps::EntityType_Wall:                  item = new RoomGraphicsItemWall(entity, cellSize);              break;
        case Screeps::EntityType_ConstructionSite:      item = new RoomGraphicsItemConstructionSite(entity, cellSize);  break;
        case Screeps::EntityType_Tombstone:             item = new RoomGraphicsItemTombstone(entity, cellSize);         break;
        case Screeps::EntityType_Storage:               item = new RoomGraphicsItemStorage(entity, cellSize);           break;
        case Screeps::EntityType_Container:             item = new RoomGraphicsItemContainer(entity, cellSize);         break;
        case Screeps::EntityType_Road:                  item = new RoomGraphicsItemRoad(entity, cellSize);              break;
        case Screeps::EntityType_Link:                  item = new RoomGraphicsItemLink(entity, cellSize);              break;
        case Screeps::EntityType_Energy:                item = new RoomGraphicsItemEnergy(entity, cellSize);            break;
        case Screeps::EntityType_Terminal:              item = new RoomGraphicsItemTerminal(entity, cellSize);          break;
        case Screeps::EntityType_Lab:                   item = new RoomGraphicsItemLab(entity, cellSize);               break;
        case Screeps::EntityType_Nuker:                 item = new RoomGraphicsItemNuker(entity, cellSize);             break;
        case Screeps::EntityType_Rampart:               item = new RoomGraphicsItemRampart(entity, cellSize);           break;
        case Screeps::EntityType_PowerSpawn:            item = new RoomGraphicsItemPowerSpawn(entity, cellSize);        break;
        case Screeps::EntityType_Observer:              item = new RoomGraphicsItemObserver(entity, cellSize);          break;

        default:                                        item = new RoomGraphicsItemUnknown(entity, cellSize);           break;
    }

    Q_ASSERT(item != nullptr);

    return item;
}

int RoomGraphicsItem::type() const {
    return _type;
}

QRectF RoomGraphicsItem::boundingRect() const {
    const qreal selectionPadding = ((_cellSize.width() / 100.0f) *  SELECTION_PADDING);
    const qreal penWidth = ((_cellSize.width() / 100.0f) * SELECTION_PEN_WIDTH);

    return itemRect().adjusted(-(penWidth + selectionPadding),
                               -(penWidth + selectionPadding),
                               penWidth + selectionPadding,
                               penWidth + selectionPadding);
}

void RoomGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->save();
    paintItem(painter, option, itemRect());
    painter->restore();

    if(isSelected ()) {
        const qreal penWidth = ((_cellSize.width() / 100.0f) * SELECTION_PEN_WIDTH);
        const QRectF bounds = boundingRect().adjusted (penWidth / 2, penWidth / 2, -(penWidth / 2), -(penWidth / 2));

        painter->setOpacity(1.0);
        painter->setPen(QPen(SELECTION_PEN_COLOR, penWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(bounds);
    }

    Q_UNUSED(widget);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RoomGraphicsItem::RoomGraphicsItem(GraphicsItemType type, const QSize& cellSize, GraphicsItemZOrder zOrder /* = ItemZOrder_Default */, QGraphicsItem* parent /* = nullptr */)
    : _super(parent), _type(type), _cellSize(cellSize) {

    setZValue(zOrder);
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
}

void RoomGraphicsItem::setPosition(int x, int y) {
    setPosition(QPoint(x, y));
}

void RoomGraphicsItem::setPosition(const QPoint& roomPos) {
    setPos(roomToScene(roomPos));
}

QPoint RoomGraphicsItem::roomToScene(int roomX, int roomY) const {
    return roomToScene(QPoint(roomX, roomY));
}

QPoint RoomGraphicsItem::roomToScene(const QPoint& roomPos) const {
    return QPoint(roomPos.x() * _cellSize.width(), roomPos.y() * _cellSize.height());
}

QPoint RoomGraphicsItem::sceneToRoom(const QPointF& point) const {
    return QPoint(point.x() / _cellSize.width(), point.y() / _cellSize.height());
}

QPoint RoomGraphicsItem::centerPoint(int roomX, int roomY) const {
    return centerPoint(QPoint(roomX, roomY));
}

QPoint RoomGraphicsItem::centerPoint(const QPoint& roomPos) const {
    return QPoint((roomPos.x() * _cellSize.width()) + _cellSize.width() / 2, (roomPos.y() * _cellSize.height()) + _cellSize.height() / 2);
}

qreal RoomGraphicsItem::angleToRoomTarget(const QPoint& roomPos) const {
    return angleToSceneTarget(roomToScene(roomPos));
}

qreal RoomGraphicsItem::angleToSceneTarget(const QPoint& scenePos) const {
    const QPointF offset = pos() - scenePos;

    //
    // Note: qAtan2() takes the y-axis before the x-axis
    //

    return qRadiansToDegrees(qAtan2(offset.y(), offset.x())) - 90;
}

QRectF RoomGraphicsItem::itemRect() const {
    const QSizeF size = itemSize(_cellSize);

    return QRectF(
        -((size.width() - _cellSize.width()) / 2),
        -((size.height() - _cellSize.height()) / 2),
        size.width(),
        size.height()
    );
}
