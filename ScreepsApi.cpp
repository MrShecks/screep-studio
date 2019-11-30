/*
 * File: ScreepsAPI.cpp
 * Created: 2018-12-17
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

#include <QStringLiteral>
#include <QHash>

#include "ScreepsApi.h"

#include <QDebug>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// REST API
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString Screeps::HTTP_HEADER_TOKEN                = QStringLiteral("X-Token");
const QString Screeps::HTTP_HEADER_USERNAME             = QStringLiteral("X-Username");
const QString Screeps::HTTP_HEADER_SERVER_PASSWORD      = QStringLiteral("X-Server-Password");

const QString Screeps::PATH_SERVER_VERSION              = QStringLiteral("/api/version");

const QString Screeps::PATH_AUTH_SIGNIN                 = QStringLiteral("/api/auth/signin");
const QString Screeps::PATH_AUTH_STEAM_TOKEN            = QStringLiteral("/api/auth/steam-ticket");
const QString Screeps::PATH_AUTH_ME                     = QStringLiteral("/api/auth/me");

const QString Screeps::PATH_AUTHMOD                     = QStringLiteral("/api/authmod");
const QString Screeps::PATH_REGISTER_USER               = QStringLiteral("/api/register/submit");

const QString Screeps::PATH_GAME_TIME                   = QStringLiteral("/api/game/time");
const QString Screeps::PATH_GAME_WORLDSIZE              = QStringLiteral("/api/game/world-size");
const QString Screeps::PATH_GAME_MAPSTATS               = QStringLiteral("/api/game/map-stats");
const QString Screeps::PATH_GAME_ROOMSTATUS             = QStringLiteral("/api/game/room-status");
const QString Screeps::PATH_GAME_ROOMOVERVIEW           = QStringLiteral("/api/game/room-overview");
const QString Screeps::PATH_GAME_ROOMTERRAIN            = QStringLiteral("/api/game/room-terrain");

const QString Screeps::PATH_USER_CONSOLE                = QStringLiteral("/api/user/console");

const QString Screeps::QUERY_ROOM_NAME                  = QStringLiteral("room");
const QString Screeps::QUERY_SHARD_NAME                 = QStringLiteral("shard");
const QString Screeps::QUERY_ENCODED                    = QStringLiteral("encoded");
const QString Screeps::QUERY_INTERVAL                   = QStringLiteral("interval");

const QString Screeps::POST_USERNAME                    = QStringLiteral("username");
const QString Screeps::POST_PASSWORD                    = QStringLiteral("password");
const QString Screeps::POST_EMAIL                       = QStringLiteral("email");

const QString Screeps::POST_AUTH_TICKET                 = QStringLiteral("ticket");
const QString Screeps::POST_AUTH_NATIVE                 = QStringLiteral("useNativeAuth");

const QString Screeps::POST_EXPRESSION                  = QStringLiteral("expression");
const QString Screeps::POST_SHARD_NAME                  = QStringLiteral("shard");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Websocket API
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString Screeps::WEBSOCKET_ENDPOINT       = QStringLiteral("/socket/websocket");

const QString Screeps::CHANNEL_USER             = QStringLiteral("user");
const QString Screeps::CHANNEL_ROOM             = QStringLiteral("room");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Game Room Constants
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

QString Screeps::getRoomName(int x, int y) {
    QString roomName;

    roomName += (x < 0) ? QString("W%1").arg(-x-1) : QString("E%1").arg(x);
    roomName += (y < 0) ? QString("N%1").arg(-y-1) : QString("S%1").arg(y);

    return roomName;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Minerals/Resources
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString Screeps::RESOURCE_NAME_ENERGY                         = QStringLiteral("energy");
const QString Screeps::RESOURCE_NAME_POWER                          = QStringLiteral("power");

const QString Screeps::RESOURCE_NAME_HYDROGEN                       = QStringLiteral("H");
const QString Screeps::RESOURCE_NAME_OXYGEN                         = QStringLiteral("O");
const QString Screeps::RESOURCE_NAME_UTRIUM                         = QStringLiteral("U");
const QString Screeps::RESOURCE_NAME_LEMERGIUM                      = QStringLiteral("L");
const QString Screeps::RESOURCE_NAME_KEANIUM                        = QStringLiteral("K");
const QString Screeps::RESOURCE_NAME_ZYNTHIUM                       = QStringLiteral("Z");
const QString Screeps::RESOURCE_NAME_CATALYST                       = QStringLiteral("X");
const QString Screeps::RESOURCE_NAME_GHODIUM                        = QStringLiteral("G");

const QString Screeps::RESOURCE_NAME_HYDROXIDE                      = QStringLiteral("OH");
const QString Screeps::RESOURCE_NAME_ZYNTHIUM_KEANITE               = QStringLiteral("ZK");
const QString Screeps::RESOURCE_NAME_UTRIUM_LEMERGITE               = QStringLiteral("UL");

const QString Screeps::RESOURCE_NAME_UTRIUM_HYDRIDE                 = QStringLiteral("UH");
const QString Screeps::RESOURCE_NAME_UTRIUM_OXIDE                   = QStringLiteral("UO");
const QString Screeps::RESOURCE_NAME_KEANIUM_HYDRIDE                = QStringLiteral("KH");
const QString Screeps::RESOURCE_NAME_KEANIUM_OXIDE                  = QStringLiteral("KO");
const QString Screeps::RESOURCE_NAME_LEMERGIUM_HYDRIDE              = QStringLiteral("LH");
const QString Screeps::RESOURCE_NAME_LEMERGIUM_OXIDE                = QStringLiteral("LO");
const QString Screeps::RESOURCE_NAME_ZYNTHIUM_HYDRIDE               = QStringLiteral("ZH");
const QString Screeps::RESOURCE_NAME_ZYNTHIUM_OXIDE                 = QStringLiteral("ZO");
const QString Screeps::RESOURCE_NAME_GHODIUM_HYDRIDE                = QStringLiteral("GH");
const QString Screeps::RESOURCE_NAME_GHODIUM_OXIDE                  = QStringLiteral("GO");

const QString Screeps::RESOURCE_NAME_UTRIUM_ACID                    = QStringLiteral("UH2O");
const QString Screeps::RESOURCE_NAME_UTRIUM_ALKALIDE                = QStringLiteral("UHO2");
const QString Screeps::RESOURCE_NAME_KEANIUM_ACID                   = QStringLiteral("KH2O");
const QString Screeps::RESOURCE_NAME_KEANIUM_ALKALIDE               = QStringLiteral("KHO2");
const QString Screeps::RESOURCE_NAME_LEMERGIUM_ACID                 = QStringLiteral("LH2O");
const QString Screeps::RESOURCE_NAME_LEMERGIUM_ALKALIDE             = QStringLiteral("LHO2");
const QString Screeps::RESOURCE_NAME_ZYNTHIUM_ACID                  = QStringLiteral("ZH2O");
const QString Screeps::RESOURCE_NAME_ZYNTHIUM_ALKALIDE              = QStringLiteral("ZHO2");
const QString Screeps::RESOURCE_NAME_GHODIUM_ACID                   = QStringLiteral("GH2O");
const QString Screeps::RESOURCE_NAME_GHODIUM_ALKALIDE               = QStringLiteral("GHO2");

const QString Screeps::RESOURCE_NAME_CATALYZED_UTRIUM_ACID          = QStringLiteral("XUH2O");
const QString Screeps::RESOURCE_NAME_CATALYZED_UTRIUM_ALKALIDE      = QStringLiteral("XUHO2");
const QString Screeps::RESOURCE_NAME_CATALYZED_KEANIUM_ACID         = QStringLiteral("XKH2O");
const QString Screeps::RESOURCE_NAME_CATALYZED_KEANIUM_ALKALIDE     = QStringLiteral("XKHO2");
const QString Screeps::RESOURCE_NAME_CATALYZED_LEMERGIUM_ACID       = QStringLiteral("XLH2O");
const QString Screeps::RESOURCE_NAME_CATALYZED_LEMERGIUM_ALKALIDE   = QStringLiteral("XLHO2");
const QString Screeps::RESOURCE_NAME_CATALYZED_ZYNTHIUM_ACID        = QStringLiteral("XZH2O");
const QString Screeps::RESOURCE_NAME_CATALYZED_ZYNTHIUM_ALKALIDE    = QStringLiteral("XZHO2");
const QString Screeps::RESOURCE_NAME_CATALYZED_GHODIUM_ACID         = QStringLiteral("XGH2O");
const QString Screeps::RESOURCE_NAME_CATALYZED_GHODIUM_ALKALIDE     = QStringLiteral("XGHO2");

const QString Screeps::RESOURCES_ALL[ResourceType_Count] = {
    RESOURCE_NAME_ENERGY,
    RESOURCE_NAME_POWER,

    RESOURCE_NAME_HYDROGEN,
    RESOURCE_NAME_OXYGEN,
    RESOURCE_NAME_UTRIUM,
    RESOURCE_NAME_LEMERGIUM,
    RESOURCE_NAME_KEANIUM,
    RESOURCE_NAME_ZYNTHIUM,
    RESOURCE_NAME_CATALYST,
    RESOURCE_NAME_GHODIUM,

    RESOURCE_NAME_HYDROXIDE,
    RESOURCE_NAME_ZYNTHIUM_KEANITE,
    RESOURCE_NAME_UTRIUM_LEMERGITE,

    RESOURCE_NAME_UTRIUM_HYDRIDE,
    RESOURCE_NAME_UTRIUM_OXIDE,
    RESOURCE_NAME_KEANIUM_HYDRIDE,
    RESOURCE_NAME_KEANIUM_OXIDE,
    RESOURCE_NAME_LEMERGIUM_HYDRIDE,
    RESOURCE_NAME_LEMERGIUM_OXIDE,
    RESOURCE_NAME_ZYNTHIUM_HYDRIDE,
    RESOURCE_NAME_ZYNTHIUM_OXIDE,
    RESOURCE_NAME_GHODIUM_HYDRIDE,
    RESOURCE_NAME_GHODIUM_OXIDE,

    RESOURCE_NAME_UTRIUM_ACID,
    RESOURCE_NAME_UTRIUM_ALKALIDE,
    RESOURCE_NAME_KEANIUM_ACID,
    RESOURCE_NAME_KEANIUM_ALKALIDE,
    RESOURCE_NAME_LEMERGIUM_ACID,
    RESOURCE_NAME_LEMERGIUM_ALKALIDE,
    RESOURCE_NAME_ZYNTHIUM_ACID,
    RESOURCE_NAME_ZYNTHIUM_ALKALIDE,
    RESOURCE_NAME_GHODIUM_ACID,
    RESOURCE_NAME_GHODIUM_ALKALIDE,

    RESOURCE_NAME_CATALYZED_UTRIUM_ACID,
    RESOURCE_NAME_CATALYZED_UTRIUM_ALKALIDE,
    RESOURCE_NAME_CATALYZED_KEANIUM_ACID,
    RESOURCE_NAME_CATALYZED_KEANIUM_ALKALIDE,
    RESOURCE_NAME_CATALYZED_LEMERGIUM_ACID,
    RESOURCE_NAME_CATALYZED_LEMERGIUM_ALKALIDE,
    RESOURCE_NAME_CATALYZED_ZYNTHIUM_ACID,
    RESOURCE_NAME_CATALYZED_ZYNTHIUM_ALKALIDE,
    RESOURCE_NAME_CATALYZED_GHODIUM_ACID,
    RESOURCE_NAME_CATALYZED_GHODIUM_ALKALIDE
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Structures
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString Screeps::STRUCTURE_SPAWN          = QStringLiteral("spawn");
const QString Screeps::STRUCTURE_EXTENSION      = QStringLiteral("extension");
const QString Screeps::STRUCTURE_ROAD           = QStringLiteral("road");
const QString Screeps::STRUCTURE_WALL           = QStringLiteral("constructedWall");
const QString Screeps::STRUCTURE_RAMPART        = QStringLiteral("rampart");
const QString Screeps::STRUCTURE_KEEPER_LAIR    = QStringLiteral("keeperLair");
const QString Screeps::STRUCTURE_PORTAL         = QStringLiteral("portal");
const QString Screeps::STRUCTURE_CONTROLLER     = QStringLiteral("controller");
const QString Screeps::STRUCTURE_LINK           = QStringLiteral("link");
const QString Screeps::STRUCTURE_STORAGE        = QStringLiteral("storage");
const QString Screeps::STRUCTURE_TOWER          = QStringLiteral("tower");
const QString Screeps::STRUCTURE_OBSERVER       = QStringLiteral("observer");
const QString Screeps::STRUCTURE_POWER_BANK     = QStringLiteral("powerBank");
const QString Screeps::STRUCTURE_POWER_SPAWN    = QStringLiteral("powerSpawn");
const QString Screeps::STRUCTURE_EXTRACTOR      = QStringLiteral("extractor");
const QString Screeps::STRUCTURE_LAB            = QStringLiteral("lab");
const QString Screeps::STRUCTURE_TERMINAL       = QStringLiteral("terminal");
const QString Screeps::STRUCTURE_CONTAINER      = QStringLiteral("container");
const QString Screeps::STRUCTURE_NUKER          = QStringLiteral("nuker");

const QHash<QString, Screeps::StructureType> Screeps::_STRUCTURETYPE_MAP = {
    { STRUCTURE_SPAWN, StructureType_Spawn              },
    { STRUCTURE_EXTENSION, StructureType_Extension      },
    { STRUCTURE_ROAD, StructureType_Road                },
    { STRUCTURE_WALL, StructureType_Wall                },
    { STRUCTURE_RAMPART, StructureType_Rampart          },
    { STRUCTURE_KEEPER_LAIR, StructureType_KeeperLair   },
    { STRUCTURE_PORTAL, StructureType_Portal            },
    { STRUCTURE_CONTROLLER, StructureType_Controller    },
    { STRUCTURE_LINK, StructureType_Link                },
    { STRUCTURE_STORAGE, StructureType_Storage          },
    { STRUCTURE_TOWER, StructureType_Tower              },
    { STRUCTURE_OBSERVER, StructureType_Observer        },
    { STRUCTURE_POWER_BANK, StructureType_PowerBank     },
    { STRUCTURE_POWER_SPAWN, StructureType_PowerSpawn   },
    { STRUCTURE_EXTRACTOR, StructureType_Extractor      },
    { STRUCTURE_LAB, StructureType_Lab                  },
    { STRUCTURE_TERMINAL, StructureType_Terminal        },
    { STRUCTURE_CONTAINER, StructureType_Container      },
    { STRUCTURE_NUKER, StructureType_Nuker              }
};

Screeps::StructureType Screeps::getStructureType(const QString& name) {
    return _STRUCTURETYPE_MAP.value(name, StructureType_Unknown);
}

QString Screeps::getStructureName(StructureType type) {
    return _STRUCTURETYPE_MAP.key(type, "<Unknown Structure Type>");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Game Entities
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString Screeps::ENTITY_CREEP             = QStringLiteral("creep");
const QString Screeps::ENTITY_SOURCE            = QStringLiteral("source");
const QString Screeps::ENTITY_MINERAL           = QStringLiteral("mineral");
const QString Screeps::ENTITY_CONSTRUCTIONSITE  = QStringLiteral("constructionSite");
const QString Screeps::ENTITY_TOMBSTONE         = QStringLiteral("tombstone");
const QString Screeps::ENTITY_ENERGY            = QStringLiteral("energy");

const QHash<QString, Screeps::EntityType> Screeps::_ENTITYTYPE_MAP = {
    { STRUCTURE_SPAWN, EntityType_Spawn                       },
    { STRUCTURE_EXTENSION, EntityType_Extension               },
    { STRUCTURE_ROAD , EntityType_Road                        },
    { STRUCTURE_WALL, EntityType_Wall                         },
    { STRUCTURE_RAMPART, EntityType_Rampart                   },
    { STRUCTURE_KEEPER_LAIR, EntityType_KeeperLair            },
    { STRUCTURE_PORTAL, EntityType_Portal                     },
    { STRUCTURE_CONTROLLER, EntityType_Controller             },
    { STRUCTURE_LINK, EntityType_Link                         },
    { STRUCTURE_TOWER, EntityType_Tower                       },
    { STRUCTURE_STORAGE, EntityType_Storage                   },
    { STRUCTURE_OBSERVER, EntityType_Observer                 },
    { STRUCTURE_POWER_BANK, EntityType_PowerBank              },
    { STRUCTURE_POWER_SPAWN, EntityType_PowerSpawn            },
    { STRUCTURE_EXTRACTOR, EntityType_Extractor               },
    { STRUCTURE_LAB, EntityType_Lab                           },
    { STRUCTURE_TERMINAL, EntityType_Terminal                 },
    { STRUCTURE_CONTAINER, EntityType_Container               },
    { STRUCTURE_NUKER, EntityType_Nuker                       },

    { ENTITY_CREEP, EntityType_Creep                          },
    { ENTITY_SOURCE, EntityType_Source                        },
    { ENTITY_MINERAL, EntityType_Mineral                      },
    { ENTITY_CONSTRUCTIONSITE, EntityType_ConstructionSite    },
    { ENTITY_TOMBSTONE, EntityType_Tombstone                  },
    { ENTITY_ENERGY, EntityType_Energy                        }
};

const QHash<Screeps::StructureType, QVector<int>> Screeps::_CONTROLLER_STRUCTURE_MAP = {
    { StructureType_Spawn, QVector<int> { 0, 1, 1, 1, 1, 1, 1, 2, 3 } },
    { StructureType_Extension, QVector<int> { 0, 0, 5, 10, 20, 30, 40, 50, 60 } },
    { StructureType_Road, QVector<int> { 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500 } },
    { StructureType_Wall, QVector<int> { 0, 0, 2500, 2500, 2500, 2500, 2500, 2500, 2500 } },
    { StructureType_Rampart, QVector<int> { 0, 0, 2500, 2500, 2500, 2500, 2500, 2500, 2500 } },
    { StructureType_Storage, QVector<int> { 0, 0, 0, 0, 1, 1, 1, 1, 1 } },
    { StructureType_Tower, QVector<int> { 0, 0, 0, 1, 1, 2, 2, 3, 6 } },
    { StructureType_Observer, QVector<int> { 0, 0, 0, 0, 0, 0, 0, 0, 1 } },
    { StructureType_PowerSpawn, QVector<int> { 0, 0, 0, 0, 0, 0, 0, 0, 1 } },
    { StructureType_Extractor, QVector<int> { 0, 0, 0, 0, 0, 0, 1, 1, 1 } },
    { StructureType_Terminal, QVector<int> { 0, 0, 0, 0, 0, 0, 1, 1, 1 } },
    { StructureType_Lab, QVector<int> { 0, 0, 0, 0, 0, 0, 3, 6, 10 } },
    { StructureType_Container, QVector<int> { 5, 5, 5, 5, 5, 5, 5, 5, 5 } },
    { StructureType_Nuker, QVector<int> { 0, 0, 0, 0, 0, 0, 0, 0, 1 } }
};

Screeps::EntityType Screeps::getEntityType(const QString& name) {
    return _ENTITYTYPE_MAP.value(name, EntityType_Unknown);
}

QString Screeps::getEntityName(EntityType type) {
    return _ENTITYTYPE_MAP.key(type, "<Unknown Entity Type>");
}

int Screeps::getAllowedStructureCount(StructureType type, int controllerLevel) {
    QHash<StructureType, QVector<int>>::const_iterator it = _CONTROLLER_STRUCTURE_MAP.find(type);
    int count = -1;

    if(it != _CONTROLLER_STRUCTURE_MAP.constEnd () && controllerLevel >= 0 && controllerLevel <= MAX_CONTROLLER_LEVEL) {
        count = it->at(controllerLevel);
    }

    return count;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Creep Body Parts
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const QString Screeps::BODYPART_MOVE            = QStringLiteral("move");
const QString Screeps::BODYPART_WORK            = QStringLiteral("work");
const QString Screeps::BODYPART_HEAL            = QStringLiteral("heal");
const QString Screeps::BODYPART_CARRY           = QStringLiteral("carry");
const QString Screeps::BODYPART_CLAIM           = QStringLiteral("claim");
const QString Screeps::BODYPART_TOUGH           = QStringLiteral("tough");
const QString Screeps::BODYPART_ATTACK          = QStringLiteral("attack");
const QString Screeps::BODYPART_RANGED_ATTACK   = QStringLiteral("ranged_attack");

const QHash<QString, Screeps::BodyPart> Screeps::_BODYPART_MAP = {
    { BODYPART_MOVE, BodyPart_Move                  },
    { BODYPART_WORK, BodyPart_Work                  },
    { BODYPART_HEAL, BodyPart_Heal                  },
    { BODYPART_CARRY, BodyPart_Carry                },
    { BODYPART_CLAIM, BodyPart_Claim                },
    { BODYPART_TOUGH, BodyPart_Tough                },
    { BODYPART_ATTACK, BodyPart_Attack              },
    { BODYPART_RANGED_ATTACK, BodyPart_RangedAttack },
};

Screeps::BodyPart Screeps::getBodyPart(const QString& name) {
    return _BODYPART_MAP.value(name, BodyPart_Unknown);
}

QString Screeps::getBodyPartName(BodyPart bodyPart) {
    return _BODYPART_MAP.key (bodyPart, "<Unknown Body Part>");
}
