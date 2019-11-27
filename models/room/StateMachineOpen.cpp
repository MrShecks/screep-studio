/*
 * File: StateMachineOpen.cpp
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

#include <QState>
#include <QFinalState>

#include "StateMachineOpen.h"
#include "RoomModel.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// StateMachineOpen
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

StateMachineOpen::StateMachineOpen(RoomModel* roomModel)
    : _super(roomModel) {

    QState* state1 = new QState();
    QState* state2 = new QState();
    QFinalState* state3 = new QFinalState();

    // State 1: Request the terrain for the room
    state1->addTransition(roomModel, &RoomModel::roomTerrainReceived, state2);
    connect(state1, &QState::entered, roomModel, &RoomModel::_refreshTerrain);

    // State 2: Subscribe to the event stream for the room
    state2->addTransition(roomModel, &RoomModel::roomEntitiesReceived, state3);
    connect(state2, &QState::entered, roomModel, &RoomModel::_refreshEntities);

    addState(state1);
    addState(state2);
    addState(state3);

    setInitialState(state1);
}

StateMachineOpen::~StateMachineOpen() {

}
