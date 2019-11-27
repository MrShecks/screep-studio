/*
 * File: ToolboxWidget.cpp
 * Created: 2018-12-26
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

#include <QListWidget>
#include <QItemDelegate>
#include <QPainter>

#include "ToolboxWidget.h"
#include "ui_ToolboxWidget.h"

#include "./room/renderers/ExtensionRenderer.h"
#include "./room/renderers/TowerRenderer.h"
#include "./room/renderers/RoadRenderer.h"
#include "./room/renderers/WallRenderer.h"
#include "./room/renderers/RampartRenderer.h"
#include "./room/renderers/ContainerRenderer.h"
#include "./room/renderers/StorageRenderer.h"
#include "./room/renderers/LinkRenderer.h"
#include "./room/renderers/ExtractorRenderer.h"
#include "./room/renderers/LabRenderer.h"
#include "./room/renderers/SpawnRenderer.h"
#include "./room/renderers/TerminalRenderer.h"
#include "./room/renderers/NukerRenderer.h"
#include "./room/renderers/PowerSpawnRenderer.h"
#include "./room/renderers/ObserverRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ToolboxItem
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ToolboxWidget::ToolboxItem::ToolboxItem(ToolboxWidget::ToolType type, const QString& title, const QString& description, const QImage& image /* = QImage() */, QListWidget* parent /* = nullptr */)
    : _super(title, parent, UserType + type),
      _description(description),
      _image(image) {
}

ToolboxWidget::ToolboxItem::~ToolboxItem() {

}

QVariant ToolboxWidget::ToolboxItem::data(int role) const {
    QVariant data;

    switch(role) {
        case ItemRoleDescription:   data = _description;            break;
        case ItemRoleImage:         data = _image;                  break;

        default:                    data = _super::data(role);      break;
    }

    return data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ToolboxItemDelegate
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ToolboxItemDelegate : public QItemDelegate {
    typedef QItemDelegate _super;

    static const int PADDING                    = 4;

    static const int TITLE_FONT_SIZE            = 12;
    static const int DESCRIPTION_FONT_SIZE      = 10;

public:
    ToolboxItemDelegate(QObject* parent = nullptr);
    virtual ~ToolboxItemDelegate();

    //
    // QItemDelegate
    //

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const Q_DECL_OVERRIDE;

private:
    QString itemTitle(const QModelIndex& index) const;
    QString itemDescription(const QModelIndex& index) const;

    void drawToolIcon(QPainter* painter, int x, int y, const QModelIndex& index) const;

    QRect getTextRectangle(const QString& text, const QRect& rect, const QFont& font) const;
    QFont getTextFont(const QFont& font, int pointSize = -1, bool bold = false) const;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ToolboxItemDelegate::ToolboxItemDelegate(QObject* parent /* = nullptr */)
    : _super(parent) {

}

ToolboxItemDelegate::~ToolboxItemDelegate() {

}

void ToolboxItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const {
    const QString title = itemTitle(index);
    const QString description = itemDescription(index);
    QRect itemRect = option.rect.adjusted(PADDING, PADDING, -PADDING, -PADDING);
    QRect textRect = itemRect.adjusted(ToolboxWidget::TOOLBOX_IMAGE_WIDTH + PADDING, 0, 0, 0);

    if((option.state & QStyle::State_Selected)) {
        painter->fillRect (option.rect, option.palette.highlight());
    }

    painter->setPen (Qt::black);

    drawToolIcon(painter, itemRect.x(), itemRect.y(), index);

    QFont titleFont = getTextFont (option.font, TITLE_FONT_SIZE, true);
    QRect titleRect = getTextRectangle(title, textRect, titleFont);

    painter->setFont(titleFont);
    painter->drawText(titleRect, Qt::TextWordWrap, title);

    textRect.adjust(0, titleRect.height(), 0, 0);

    QFont descriptionFont = getTextFont (option.font, DESCRIPTION_FONT_SIZE, false);
    QRect descriptionRect = getTextRectangle(description, textRect, descriptionFont);

    painter->setFont(descriptionFont);
    painter->drawText(descriptionRect, Qt::TextWordWrap, description);

}

QSize ToolboxItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const {
    const QString title = itemTitle(index);
    const QString description = itemDescription(index);
    QRect itemRect = option.rect.adjusted(PADDING, PADDING, -PADDING, -PADDING);
    QRect textRect = itemRect.adjusted(ToolboxWidget::TOOLBOX_IMAGE_WIDTH + PADDING, 0, 0, 0);

    QRect titleRect = getTextRectangle(title, textRect, getTextFont (option.font, TITLE_FONT_SIZE, true));

    textRect.adjust(0, titleRect.height(), 0, 0);
    QRect descriptionRect = getTextRectangle(description, textRect, getTextFont (option.font, DESCRIPTION_FONT_SIZE, false));

    int height = PADDING + titleRect.height () + PADDING + descriptionRect.height () + PADDING;

    return QSize(option.rect.width(), qMax(height, PADDING + ToolboxWidget::TOOLBOX_IMAGE_WIDTH + PADDING));
}

QString ToolboxItemDelegate::itemTitle(const QModelIndex& index) const {
    return index.data(Qt::DisplayRole).toString();
}

QString ToolboxItemDelegate::itemDescription(const QModelIndex& index) const {
    return index.data(ToolboxWidget::ToolboxItem::ItemRoleDescription).toString();
}

void ToolboxItemDelegate::drawToolIcon(QPainter* painter, int x, int y, const QModelIndex& index) const {
    QImage image = index.data (ToolboxWidget::ToolboxItem::ItemRoleImage).value<QImage>();

    if(!image.isNull())
        painter->drawImage (x, y, image);

    painter->setPen(Qt::black);
    painter->drawRect(x, y, ToolboxWidget::TOOLBOX_IMAGE_WIDTH, ToolboxWidget::TOOLBOX_IMAGE_HEIGHT);
}

QRect ToolboxItemDelegate::getTextRectangle(const QString& text, const QRect& rect, const QFont& font) const {
    const QFontMetrics fontMetrics(font);

    return fontMetrics.boundingRect(rect, Qt::TextWordWrap, text);
}

QFont ToolboxItemDelegate::getTextFont(const QFont& font, int pointSize /* = -1 */, bool bold /* = false */) const {
    QFont textFont(font);

    textFont.setPointSize (pointSize == -1 ? font.pointSize () : pointSize);
    textFont.setBold(bold);

    return textFont;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ToolboxWidget()
// UI component to display the user tool palette
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ToolboxWidget::ToolboxWidget(QWidget* parent /* = nullptr */)
    : _super(parent),
      _ui(new Ui::ToolboxWidget) {

    _ui->setupUi(this);

    addItem(ToolType_Selector, tr("Selection"), tr("Select room entities. Hold the control key and use the mouse wheel to zoom."));
    addItem(ToolType_Extension, tr("Extension"), tr("Contains additional energy which can be used by spawns for spawning bigger creeps."));
    addItem(ToolType_Road, tr("Road"), tr("Decreases movement cost. Decays over time and requires repair."));
    addItem(ToolType_Wall, tr("Wall"), tr("Blocks movement of all creeps. Requires repair after construction."));
    addItem(ToolType_Rampart, tr("Rampart"), tr("Defends creeps and structures on the same tile and blocks enemy movement. Decays over time and requires repair."));
    addItem(ToolType_Tower, tr("Tower"), tr("Remotely attacks or heals any creep in the room, or repairs structures."));

    addItem(ToolType_Container, tr("Container"), tr("Stores upto 2,000 resource units. Decays over time and requires repair."));
    addItem(ToolType_Storage, tr("Storage"), tr("Stores upto 1,000,000 resource units."));
    addItem(ToolType_Link, tr("Link"), tr("Remotely transfers energy to another Link in the same room."));
    addItem(ToolType_Extractor, tr("Extractor"), tr("Allows mining of mineral deposits."));
    addItem(ToolType_Lab, tr("Lab"), tr("Produces mineral compounds and boosts creeps."));
    addItem(ToolType_Terminal, tr("Terminal"), tr("Sends any resource to a Terminal in another room."));
    addItem(ToolType_Spawn, tr("Spawn"), tr("Spawns creeps using energy contained in the room spawns and extensions."));
    addItem(ToolType_Observer, tr("Observer"), tr("Provides visibility into a distant room from your script."));
    addItem(ToolType_PowerSpawn, tr("Power Spawn"), tr("Spawns power creeps with special unique powers."));
    addItem(ToolType_Nuker, tr("Nuker"), tr("Launches a nuke to a distant room dealing huge damage to the landing area."));

    _ui->toolList->setItemDelegate (new ToolboxItemDelegate(this));
}

ToolboxWidget::~ToolboxWidget() {
    delete _ui;
}

ToolboxWidget::ToolboxItem* ToolboxWidget::addItem(ToolType type, const QString& title, const QString& description) {
    //QColor("#2b2b#2b")
    const QSize size(ToolboxWidget::TOOLBOX_IMAGE_WIDTH, ToolboxWidget::TOOLBOX_IMAGE_HEIGHT);
    ToolboxItem* item = new ToolboxItem(type, title, description, getImage(type, size, QColor("#3a3a3a")));

    _ui->toolList->addItem(item);

    return item;
}

//enum ToolType {
//    ToolType_Selector                   = 0,
//    ToolType_Extension,
//    ToolType_Road,
//    ToolType_Wall,
//    ToolType_Rampart,
//    ToolType_Tower,
//    ToolType_Container,
//    ToolType_Storage,
//    ToolType_Link,
//    ToolType_Extractor,
//    ToolType_Lab,
//    ToolType_Terminal,
//    ToolType_Spawn,
//    ToolType_Observer,
//    ToolType_PowerSpawn,
//    ToolType_Nuker,

//    ToolType_Count
//};


QImage ToolboxWidget::getImage(ToolType type, const QSize& size, QColor fillColor) const {
    QImage image;

    switch(type) {
        case ToolType_Extension:        image = ExtensionRenderer::toImage(size, fillColor, QSize(10, 10));     break;
        case ToolType_Road:             image = RoadRenderer::toImage(size, fillColor, QSize(10, 10));          break;
        case ToolType_Wall:             image = WallRenderer::toImage (size, fillColor, QSize(10, 10));         break;
        case ToolType_Rampart:          image = RampartRenderer::toImage (size, fillColor, QSize(10, 10));      break;
        case ToolType_Tower:            image = TowerRenderer::toImage(size, fillColor, QSize(5, 5));           break;
        case ToolType_Container:        image = ContainerRenderer::toImage(size, fillColor, QSize(20, 15));     break;
        case ToolType_Storage:          image = StorageRenderer::toImage(size, fillColor, QSize(15, 10));       break;
        case ToolType_Link:             image = LinkRenderer::toImage(size, fillColor, QSize(15, 10));          break;
        case ToolType_Extractor:        image = ExtractorRenderer::toImage(size, fillColor, QSize(10, 10));     break;
        case ToolType_Lab:              image = LabRenderer::toImage (size, fillColor, QSize(5, 5));            break;
        case ToolType_Terminal:         image = TerminalRenderer::toImage(size, fillColor, QSize(5, 5));        break;
        case ToolType_Spawn:            image = SpawnRenderer::toImage(size, fillColor, QSize(5, 5));           break;
        case ToolType_Observer:         image = ObserverRenderer::toImage(size, fillColor, QSize(10, 10));      break;
        case ToolType_PowerSpawn:       image = PowerSpawnRenderer::toImage(size, fillColor, QSize(5, 5));      break;
        case ToolType_Nuker:            image = NukerRenderer::toImage(size, fillColor, QSize(10, 5));          break;
    }

    return image;
}
