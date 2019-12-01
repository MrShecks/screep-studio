/*
 * File: MineralRenderer.cpp
 * Created: 2018-12-28
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

#include "MineralRenderer.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const MineralRenderer::TMineralColorMap MineralRenderer::_FOREGROUND_COLORS = {
    { Screeps::RESOURCE_NAME_LEMERGIUM,     QColor("#89faa5")    },
    { Screeps::RESOURCE_NAME_UTRIUM,        QColor("#88d6f7")    },
    { Screeps::RESOURCE_NAME_KEANIUM,       QColor("#9370ff")    },
    { Screeps::RESOURCE_NAME_ZYNTHIUM,      QColor("#f2d28b")    },
    { Screeps::RESOURCE_NAME_CATALYST,      QColor("#ff7a7a")    },
    { Screeps::RESOURCE_NAME_OXYGEN,        QColor("#cccccc")    },
    { Screeps::RESOURCE_NAME_HYDROGEN,      QColor("#cccccc")    }
};

const MineralRenderer::TMineralColorMap MineralRenderer::_BACKGROUND_COLORS = {
    { Screeps::RESOURCE_NAME_LEMERGIUM,     QColor("#3f6147")    },
    { Screeps::RESOURCE_NAME_UTRIUM,        QColor("#1b617f")    },
    { Screeps::RESOURCE_NAME_KEANIUM,       QColor("#331a80")    },
    { Screeps::RESOURCE_NAME_ZYNTHIUM,      QColor("#594d33")    },
    { Screeps::RESOURCE_NAME_CATALYST,      QColor("#4f2626")    },
    { Screeps::RESOURCE_NAME_OXYGEN,        QColor("#4d4d4d")    },
    { Screeps::RESOURCE_NAME_HYDROGEN,      QColor("#4d4d4d")    }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MineralRenderer
// Utility class to draw the "Mineral" game entity
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MineralRenderer::MineralRenderer(QObject* parent /* = nullptr */)
    : _super(parent),
      _mineralType("?"),
      _foregroundColor(Qt::white),
      _backgroundColor(Qt::black)  {

}

MineralRenderer::~MineralRenderer() {

}

void MineralRenderer::setMineralType(const QString& mineralType) {
    _mineralType = mineralType;
    _foregroundColor = foregroundColor(mineralType);
    _backgroundColor = backgroundColor(mineralType);
    setDirty(true);
}

QColor MineralRenderer::foregroundColor() const {
    return foregroundColor(_mineralType);
}

QColor MineralRenderer::backgroundColor() const {
    return backgroundColor(_mineralType);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QColor MineralRenderer::foregroundColor(const QString& mineralType, QColor defaultColor /* = Qt::white */) const {
    return _FOREGROUND_COLORS.value(mineralType, defaultColor);
}

QColor MineralRenderer::backgroundColor(const QString& mineralType, QColor defaultColor /* = Qt::black */) const {
    return _BACKGROUND_COLORS.value(mineralType, defaultColor);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QSizeF MineralRenderer::size(const QSize& cellSize) const {
    const qreal width = scaledWidth(cellSize, ENTITY_WIDTH);
    const qreal height = scaledHeight(cellSize, ENTITY_HEIGHT);

    return QSize(width + (BORDER_PEN_WIDTH / 2), height + (BORDER_PEN_WIDTH / 2));
}

void MineralRenderer::draw(QPainter* painter, const QRectF& bounds) const {
    const qreal mineralFontSize = scaledWidth(bounds.size(), FONT_SIZE_SCALE);
    const QFont serifFont("Monospace", mineralFontSize, QFont::Bold);

    painter->setBrush(_backgroundColor);
    painter->setPen(QPen(_foregroundColor, BORDER_PEN_WIDTH));
    painter->drawEllipse(bounds);

    painter->setFont(serifFont);
    painter->drawText(bounds, Qt::AlignCenter, _mineralType);
}
