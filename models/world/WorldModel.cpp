/*
 * File: WorldModel.cpp
 * Created: 2019-1-28
 *
 * Copyright (c) shecks 2019 <shecks@gmail.com>
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

#include "WorldModel.h"
#include "network/rest/GameInfo.h"

#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// WorldModel()
// Representation of a world shard
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

WorldModel::WorldModel(NetworkModel* networkModel, QObject* parent /* = nullptr */)
    : _super(parent),
      _networkModel(networkModel) {

    connect(_networkModel, &NetworkModel::worldSizeReceived, this, &WorldModel::_onWorldSizeReceived);
}

WorldModel::~WorldModel() {

}

void WorldModel::open(const QString &shardName) {
    Q_ASSERT(_networkModel != nullptr);

    _networkModel->getWorldSize(shardName);
}

void WorldModel::close() {

}

bool WorldModel::isOpen() const {
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WorldModel::_onWorldSizeReceived(const WorldSizeResponse& response) {
    qDebug() << "Response=" << response.toString();
}

// From /@screeps/common/index.js
//
//exports.roomNameToXY = function(name) {
//
//    name = name.toUpperCase();
//
//    var match = name.match(/^(\w)(\d+)(\w)(\d+)$/);
//    if(!match) {
//        return [undefined, undefined];
//    }
//    var [,hor,x,ver,y] = match;
//
//    if(hor == 'W') {
//        x = -x-1;
//    }
//    else {
//        x = +x;
//    }
//    if(ver == 'N') {
//        y = -y-1;
//    }
//    else {
//        y = +y;
//    }
//    return [x,y];
//};
//

//exports.calcWorldSize = function(rooms) {
//    var minX = Infinity, minY = Infinity, maxX = 0, maxY = 0;
//    rooms.forEach(room => {
//        var [x,y] = exports.roomNameToXY(room._id);
//        if(x < minX) minX = x;
//        if(y < minY) minY = y;
//        if(x > maxX) maxX = x;
//        if(y > maxY) maxY = y;
//    });
//    return Math.max(maxX - minX + 1, maxY - minY + 1);
//};

// From /@screeps/engine/src/utils.js
//
//exports.getRoomNameFromXY = function(x,y) {
//    if(x < 0) {
//        x = 'W'+(-x-1);
//    }
//    else {
//        x = 'E'+(x);
//    }
//    if(y < 0) {
//        y = 'N'+(-y-1);
//    }
//    else {
//        y = 'S'+(y);
//    }
//    return ""+x+y;
//};

//{
//  "rooms": [
//    "W19N7",
//    "W18N7",
//    "W17N7",
//    "W16N7",
//    "W15N7",
//    "W14N7",
//    "W13N7",
//    "W12N7",
//    "W11N7",
//    "W10N7",
//    "W9N7",
//    "W8N7",
//    "W7N7",
//    "W6N7",
//    "W5N7",
//    "W4N7",
//    "W3N7",
//    "W2N7",
//    "W1N7",
//    "W0N7",
//    "E0N7",
//    "E1N7",
//    "E2N7",
//    "W19N6",
//    "W18N6",
//    "W17N6",
//    "W16N6",
//    "W15N6",
//    "W14N6",
//    "W13N6",
//    "W12N6",
//    "W11N6",
//    "W10N6",
//    "W9N6",
//    "W8N6",
//    "W7N6",
//    "W6N6",
//    "W5N6",
//    "W4N6",
//    "W3N6",
//    "W2N6",
//    "W1N6",
//    "W0N6",
//    "E0N6",
//    "E1N6",
//    "E2N6",
//    "W19N5",
//    "W18N5",
//    "W17N5",
//    "W16N5",
//    "W15N5",
//    "W14N5",
//    "W13N5",
//    "W12N5",
//    "W11N5",
//    "W10N5",
//    "W9N5",
//    "W8N5",
//    "W7N5",
//    "W6N5",
//    "W5N5",
//    "W4N5",
//    "W3N5",
//    "W2N5",
//    "W1N5",
//    "W0N5",
//    "E0N5",
//    "E1N5",
//    "E2N5",
//    "W19N4",
//    "W18N4",
//    "W17N4",
//    "W16N4",
//    "W15N4",
//    "W14N4",
//    "W13N4",
//    "W12N4",
//    "W11N4",
//    "W10N4",
//    "W9N4",
//    "W8N4",
//    "W7N4",
//    "W6N4",
//    "W5N4",
//    "W4N4",
//    "W3N4",
//    "W2N4",
//    "W1N4",
//    "W0N4",
//    "E0N4",
//    "E1N4",
//    "E2N4",
//    "W19N3",
//    "W18N3",
//    "W17N3",
//    "W16N3",
//    "W15N3",
//    "W14N3",
//    "W13N3",
//    "W12N3",
//    "W11N3",
//    "W10N3",
//    "W9N3",
//    "W8N3",
//    "W7N3",
//    "W6N3",
//    "W5N3",
//    "W4N3",
//    "W3N3",
//    "W2N3",
//    "W1N3",
//    "W0N3",
//    "E0N3",
//    "E1N3",
//    "E2N3",
//    "W19N2",
//    "W18N2",
//    "W17N2",
//    "W16N2",
//    "W15N2",
//    "W14N2",
//    "W13N2",
//    "W12N2",
//    "W11N2",
//    "W10N2",
//    "W9N2",
//    "W8N2",
//    "W7N2",
//    "W6N2",
//    "W5N2",
//    "W4N2",
//    "W3N2",
//    "W2N2",
//    "W1N2",
//    "W0N2",
//    "E0N2",
//    "E1N2",
//    "E2N2",
//    "W19N1",
//    "W18N1",
//    "W17N1",
//    "W16N1",
//    "W15N1",
//    "W14N1",
//    "W13N1",
//    "W12N1",
//    "W11N1",
//    "W10N1",
//    "W9N1",
//    "W8N1",
//    "W7N1",
//    "W6N1",
//    "W5N1",
//    "W4N1",
//    "W3N1",
//    "W2N1",
//    "W1N1",
//    "W0N1",
//    "E0N1",
//    "E1N1",
//    "E2N1",
//    "W19N0",
//    "W18N0",
//    "W17N0",
//    "W16N0",
//    "W15N0",
//    "W14N0",
//    "W13N0",
//    "W12N0",
//    "W11N0",
//    "W10N0",
//    "W9N0",
//    "W8N0",
//    "W7N0",
//    "W6N0",
//    "W5N0",
//    "W4N0",
//    "W3N0",
//    "W2N0",
//    "W1N0",
//    "W0N0",
//    "E0N0",
//    "E1N0",
//    "E2N0",
//    "W19S0",
//    "W18S0",
//    "W17S0",
//    "W16S0",
//    "W15S0",
//    "W14S0",
//    "W13S0",
//    "W12S0",
//    "W11S0",
//    "W10S0",
//    "W9S0",
//    "W8S0",
//    "W7S0",
//    "W6S0",
//    "W5S0",
//    "W4S0",
//    "W3S0",
//    "W2S0",
//    "W1S0",
//    "W0S0",
//    "E0S0",
//    "E1S0",
//    "E2S0"
//  ],
//  "shard": "shard0",
//  "statName": "owner0"
//}
