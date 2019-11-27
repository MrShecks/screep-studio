/*
 * File: ScreepsAPI.h
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

#ifndef _SCREEPSAPI_H
#define _SCREEPSAPI_H

#include <QString>
#include <QHash>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Screeps
// Constants and types for Screeps server protocol and APIs
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Screeps {

public:

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // REST API
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static const QString HTTP_HEADER_TOKEN;
    static const QString HTTP_HEADER_USERNAME;
    static const QString HTTP_HEADER_SERVER_PASSWORD;

    static const QString PATH_SERVER_VERSION;

    static const QString PATH_AUTH_SIGNIN;
    static const QString PATH_AUTH_STEAM_TOKEN;
    static const QString PATH_AUTH_ME;

    static const QString PATH_AUTHMOD;

    static const QString PATH_GAME_TIME;
    static const QString PATH_GAME_WORLDSIZE;
    static const QString PATH_GAME_MAPSTATS;
    static const QString PATH_GAME_ROOMSTATUS;
    static const QString PATH_GAME_ROOMOVERVIEW;
    static const QString PATH_GAME_ROOMTERRAIN;

    static const QString PATH_USER_CONSOLE;

    static const QString QUERY_ROOM_NAME;
    static const QString QUERY_SHARD_NAME;
    static const QString QUERY_ENCODED;
    static const QString QUERY_INTERVAL;

    static const QString POST_EMAIL;
    static const QString POST_PASSWORD;

    static const QString POST_AUTH_TICKET;
    static const QString POST_AUTH_NATIVE;

    static const QString POST_EXPRESSION;
    static const QString POST_SHARD_NAME;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Websocket API
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static const QString WEBSOCKET_ENDPOINT;

    static const QString CHANNEL_USER;
    static const QString CHANNEL_ROOM;


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // General Error Codes
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    enum Result {
        ERR_OK                         =  0,
        ERR_NOT_OWNER                  = -1,
        ERR_NO_PATH                    = -2,
        ERR_NAME_EXISTS                = -3,
        ERR_BUSY                       = -4,
        ERR_NOT_FOUND                  = -5,
        ERR_NOT_ENOUGH_ENERGY          = -6,
        ERR_NOT_ENOUGH_RESOURCES       = -6,
        ERR_NOT_ENOUGH_EXTENSIONS      = -6,
        ERR_INVALID_TARGET             = -7,
        ERR_FULL                       = -8,
        ERR_NOT_IN_RANGE               = -9,
        ERR_INVALID_ARGS               = -10,
        ERR_TIRED                      = -11,
        ERR_NO_BODYPART                = -12,
        ERR_RCL_NOT_ENOUGH             = -14,
        ERR_GCL_NOT_ENOUGH             = -15
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Game Constants
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static const int USER_ID_INVADER            = 2;
    static const int USER_ID_SOURCE_KEEPER      = 3;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Room Constants
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static const int ROOM_WIDTH                 = 50;
    static const int ROOM_HEIGHT                = 50;

    static const int MAX_CONTROLLER_LEVEL       = 8;

    static const int MAX_DROPPED_ENERGY         = 1250;

    static const int TERRAIN_MASK_WALL          = 0x01;
    static const int TERRAIN_MASK_SWAMP         = 0x02;
    static const int TERRAIN_MASK_LAVA          = 0x04;

    // Note: Once the terrain information is received from the server
    // the terrain type mask are translated into the following enums.

    enum TerrainType {
        TerrainType_Plain                       = 0,
        TerrainType_Wall                        = 1,
        TerrainType_Swamp                       = 2,
        TerrainType_Lava                        = 3,

        TerrainType_Count
    };

    enum TerrainFlag {
        TerrainFlag_None                        = 0,

        TerrainFlag_Plain                       = 1 << TerrainType_Plain,
        TerrainFlag_Wall                        = 1 << TerrainType_Wall,
        TerrainFlag_Swamp                       = 1 << TerrainType_Swamp,
        TerrainFlag_Lava                        = 1 << TerrainType_Lava,

        TerrainFlag_SwampyWall                  = TerrainFlag_Swamp | TerrainFlag_Wall
    };

    Q_DECLARE_FLAGS(TerrainFlags, TerrainFlag)

    static QString getRoomName(int x, int y);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Structures
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    enum StructureType {
        StructureType_Unknown = -1,

        StructureType_Spawn,
        StructureType_Extension,
        StructureType_Road,
        StructureType_Wall,
        StructureType_Rampart,
        StructureType_KeeperLair,
        StructureType_Portal,
        StructureType_Controller,
        StructureType_Link,
        StructureType_Tower,
        StructureType_Storage,
        StructureType_Observer,
        StructureType_PowerBank,
        StructureType_PowerSpawn,
        StructureType_Extractor,
        StructureType_Lab,
        StructureType_Terminal,
        StructureType_Container,
        StructureType_Nuker,

        StructureType_Count
    };

    static const QString STRUCTURE_SPAWN;
    static const QString STRUCTURE_EXTENSION;
    static const QString STRUCTURE_ROAD;
    static const QString STRUCTURE_WALL;
    static const QString STRUCTURE_RAMPART;
    static const QString STRUCTURE_KEEPER_LAIR;
    static const QString STRUCTURE_PORTAL;
    static const QString STRUCTURE_CONTROLLER;
    static const QString STRUCTURE_LINK;
    static const QString STRUCTURE_STORAGE;
    static const QString STRUCTURE_TOWER;
    static const QString STRUCTURE_OBSERVER;
    static const QString STRUCTURE_POWER_BANK;
    static const QString STRUCTURE_POWER_SPAWN;
    static const QString STRUCTURE_EXTRACTOR;
    static const QString STRUCTURE_LAB;
    static const QString STRUCTURE_TERMINAL;
    static const QString STRUCTURE_CONTAINER;
    static const QString STRUCTURE_NUKER;

    static StructureType getStructureType(const QString& name);
    static QString getStructureName(StructureType type);

    static int getAllowedStructureCount(StructureType type, int controllerLevel);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Game Entities
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    enum EntityType {
        EntityType_Unknown                      = StructureType_Unknown,

        EntityType_Spawn                        = StructureType_Spawn,
        EntityType_Extension                    = StructureType_Extension,
        EntityType_Road                         = StructureType_Road,
        EntityType_Wall                         = StructureType_Wall,
        EntityType_Rampart                      = StructureType_Rampart,
        EntityType_KeeperLair                   = StructureType_KeeperLair,
        EntityType_Portal                       = StructureType_Portal,
        EntityType_Controller                   = StructureType_Controller,
        EntityType_Link                         = StructureType_Link,
        EntityType_Tower                        = StructureType_Tower,
        EntityType_Storage                      = StructureType_Storage,
        EntityType_Observer                     = StructureType_Observer,
        EntityType_PowerBank                    = StructureType_PowerBank,
        EntityType_PowerSpawn                   = StructureType_PowerSpawn,
        EntityType_Extractor                    = StructureType_Extractor,
        EntityType_Lab                          = StructureType_Lab,
        EntityType_Terminal                     = StructureType_Terminal,
        EntityType_Container                    = StructureType_Container,
        EntityType_Nuker                        = StructureType_Nuker,

        EntityType_Creep,
        EntityType_Source,
        EntityType_Mineral,
        EntityType_ConstructionSite,
        EntityType_Tombstone,
        EntityType_Energy
    };

    static const QString ENTITY_CREEP;
    static const QString ENTITY_SOURCE;
    static const QString ENTITY_MINERAL;
    static const QString ENTITY_CONSTRUCTIONSITE;
    static const QString ENTITY_TOMBSTONE;
    static const QString ENTITY_ENERGY;

    static EntityType getEntityType(const QString& entityName);
    static QString getEntityName(EntityType type);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Creep Body Parts
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static const int MAX_CREEP_BODY_PARTS       = 50;
    static const int MAX_CREEP_BODY_PART_HITS   = 100;

    static const int CARRY_CAPACITY             = 50;

    enum BodyPart {
        BodyPart_Unknown                        = -1,

        BodyPart_Move,
        BodyPart_Work,
        BodyPart_Heal,
        BodyPart_Carry,
        BodyPart_Claim,
        BodyPart_Tough,
        BodyPart_Attack,
        BodyPart_RangedAttack,

        BodyPart_Count
    };

    static const QString BODYPART_MOVE;
    static const QString BODYPART_WORK;
    static const QString BODYPART_HEAL;
    static const QString BODYPART_CARRY;
    static const QString BODYPART_CLAIM;
    static const QString BODYPART_TOUGH;
    static const QString BODYPART_ATTACK;
    static const QString BODYPART_RANGED_ATTACK;

    static BodyPart getBodyPart(const QString& name);
    static QString getBodyPartName(BodyPart bodyPart);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Minerals/Resource
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    enum ResourceType {
        ResourceType_ENERGY,
        ResourceType_POWER,

        ResourceType_HYDROGEN,
        ResourceType_OXYGEN,
        ResourceType_UTRIUM,
        ResourceType_LEMERGIUM,
        ResourceType_KEANIUM,
        ResourceType_ZYNTHIUM,
        ResourceType_CATALYST,
        ResourceType_GHODIUM,

        ResourceType_HYDROXIDE,
        ResourceType_ZYNTHIUM_KEANITE,
        ResourceType_UTRIUM_LEMERGITE,

        ResourceType_UTRIUM_HYDRIDE,
        ResourceType_UTRIUM_OXIDE,
        ResourceType_KEANIUM_HYDRIDE,
        ResourceType_KEANIUM_OXIDE,
        ResourceType_LEMERGIUM_HYDRIDE,
        ResourceType_LEMERGIUM_OXIDE,
        ResourceType_ZYNTHIUM_HYDRIDE,
        ResourceType_ZYNTHIUM_OXIDE,
        ResourceType_GHODIUM_HYDRIDE,
        ResourceType_GHODIUM_OXIDE,

        ResourceType_UTRIUM_ACID,
        ResourceType_UTRIUM_ALKALIDE,
        ResourceType_KEANIUM_ACID,
        ResourceType_KEANIUM_ALKALIDE,
        ResourceType_LEMERGIUM_ACID,
        ResourceType_LEMERGIUM_ALKALIDE,
        ResourceType_ZYNTHIUM_ACID,
        ResourceType_ZYNTHIUM_ALKALIDE,
        ResourceType_GHODIUM_ACID,
        ResourceType_GHODIUM_ALKALIDE,

        ResourceType_CATALYZED_UTRIUM_ACID,
        ResourceType_CATALYZED_UTRIUM_ALKALIDE,
        ResourceType_CATALYZED_KEANIUM_ACID,
        ResourceType_CATALYZED_KEANIUM_ALKALIDE,
        ResourceType_CATALYZED_LEMERGIUM_ACID,
        ResourceType_CATALYZED_LEMERGIUM_ALKALIDE,
        ResourceType_CATALYZED_ZYNTHIUM_ACID,
        ResourceType_CATALYZED_ZYNTHIUM_ALKALIDE,
        ResourceType_CATALYZED_GHODIUM_ACID,
        ResourceType_CATALYZED_GHODIUM_ALKALIDE,

        ResourceType_Count
    };

    static const QString RESOURCE_NAME_ENERGY;
    static const QString RESOURCE_NAME_POWER;

    static const QString RESOURCE_NAME_HYDROGEN;
    static const QString RESOURCE_NAME_OXYGEN;
    static const QString RESOURCE_NAME_UTRIUM;
    static const QString RESOURCE_NAME_LEMERGIUM;
    static const QString RESOURCE_NAME_KEANIUM;
    static const QString RESOURCE_NAME_ZYNTHIUM;
    static const QString RESOURCE_NAME_CATALYST;
    static const QString RESOURCE_NAME_GHODIUM;

    static const QString RESOURCE_NAME_HYDROXIDE;
    static const QString RESOURCE_NAME_ZYNTHIUM_KEANITE;
    static const QString RESOURCE_NAME_UTRIUM_LEMERGITE;

    static const QString RESOURCE_NAME_UTRIUM_HYDRIDE;
    static const QString RESOURCE_NAME_UTRIUM_OXIDE;
    static const QString RESOURCE_NAME_KEANIUM_HYDRIDE;
    static const QString RESOURCE_NAME_KEANIUM_OXIDE;
    static const QString RESOURCE_NAME_LEMERGIUM_HYDRIDE;
    static const QString RESOURCE_NAME_LEMERGIUM_OXIDE;
    static const QString RESOURCE_NAME_ZYNTHIUM_HYDRIDE;
    static const QString RESOURCE_NAME_ZYNTHIUM_OXIDE;
    static const QString RESOURCE_NAME_GHODIUM_HYDRIDE;
    static const QString RESOURCE_NAME_GHODIUM_OXIDE;

    static const QString RESOURCE_NAME_UTRIUM_ACID;
    static const QString RESOURCE_NAME_UTRIUM_ALKALIDE;
    static const QString RESOURCE_NAME_KEANIUM_ACID;
    static const QString RESOURCE_NAME_KEANIUM_ALKALIDE;
    static const QString RESOURCE_NAME_LEMERGIUM_ACID;
    static const QString RESOURCE_NAME_LEMERGIUM_ALKALIDE;
    static const QString RESOURCE_NAME_ZYNTHIUM_ACID;
    static const QString RESOURCE_NAME_ZYNTHIUM_ALKALIDE;
    static const QString RESOURCE_NAME_GHODIUM_ACID;
    static const QString RESOURCE_NAME_GHODIUM_ALKALIDE;

    static const QString RESOURCE_NAME_CATALYZED_UTRIUM_ACID;
    static const QString RESOURCE_NAME_CATALYZED_UTRIUM_ALKALIDE;
    static const QString RESOURCE_NAME_CATALYZED_KEANIUM_ACID;
    static const QString RESOURCE_NAME_CATALYZED_KEANIUM_ALKALIDE;
    static const QString RESOURCE_NAME_CATALYZED_LEMERGIUM_ACID;
    static const QString RESOURCE_NAME_CATALYZED_LEMERGIUM_ALKALIDE;
    static const QString RESOURCE_NAME_CATALYZED_ZYNTHIUM_ACID;
    static const QString RESOURCE_NAME_CATALYZED_ZYNTHIUM_ALKALIDE;
    static const QString RESOURCE_NAME_CATALYZED_GHODIUM_ACID;
    static const QString RESOURCE_NAME_CATALYZED_GHODIUM_ALKALIDE;

    static const QString RESOURCES_ALL[ResourceType_Count];

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    static const QHash<QString, StructureType> _STRUCTURETYPE_MAP;
    static const QHash<QString, EntityType> _ENTITYTYPE_MAP;
    static const QHash<QString, BodyPart> _BODYPART_MAP;

    static const QHash<StructureType, QVector<int>> _CONTROLLER_STRUCTURE_MAP;

    Screeps() {
        // No instances
    }

};

Q_DECLARE_OPERATORS_FOR_FLAGS(Screeps::TerrainFlags);

#endif // _SCREEPSAPI_H
