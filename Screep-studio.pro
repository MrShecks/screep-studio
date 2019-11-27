#-------------------------------------------------
#
# Project created by QtCreator 2018-11-24T14:00:03
#
#-------------------------------------------------

QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Screep-studio
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        MainWindow.cpp \
    models/room/RoomModel.cpp \
    models/room/RoomTerrainModel.cpp \
    ScreepStudioApplication.cpp \
    models/room/StorageRoomEntity.cpp \
    utils/JSONUtils.cpp \
    network/rest/RESTRoomOverview.cpp \
    network/rest/Badge.cpp \
    widgets/PropertiesWidget.cpp \
    widgets/ConsoleWidget.cpp \
    network/socket/SocketCommandAuth.cpp \
    network/socket/SocketCommandSubscribe.cpp \
    models/console/ConsoleModel.cpp \
    models/server/ServerInfoModel.cpp \
    models/NetworkModel.cpp \
    network/RestNetworkManager.cpp \
    network/SocketNetworkManager.cpp \
    network/rest/RestServerInfo.cpp \
    network/rest/RestUserInfo.cpp \
    models/user/UserInfoModel.cpp \
    network/socket/SocketEventConsole.cpp \
    network/socket/SocketEventUser.cpp \
    network/socket/SocketEventRoom.cpp \
    network/rest/RestRoomTerrain.cpp \
    widgets/room/RoomGraphicsView.cpp \
    widgets/room/RoomGraphicsScene.cpp \
    widgets/room/entities/RoomGraphicsItem.cpp \
    widgets/room/entities/RoomGraphicsItemCreep.cpp \
    widgets/room/entities/RoomGraphicsItemConstructionSite.cpp \
    widgets/room/entities/RoomGraphicsItemSource.cpp \
    widgets/room/entities/RoomGraphicsItemUnknown.cpp \
    widgets/room/entities/RoomGraphicsItemSpawn.cpp \
    widgets/room/entities/RoomGraphicsItemController.cpp \
    widgets/room/entities/RoomGraphicsItemMineral.cpp \
    widgets/room/entities/RoomGraphicsItemExtension.cpp \
    Preferences.cpp \
    models/room/StateMachineOpen.cpp \
    utils/JSONTreeModel.cpp \
    widgets/InspectorWidget.cpp \
    widgets/room/entities/RoomGraphicsItemWall.cpp \
    widgets/CreepViewWidget.cpp \
    ScreepsApi.cpp \
    widgets/room/entities/GraphicsItemSelection.cpp \
    widgets/room/utils/Tileset.cpp \
    widgets/room/utils/TerrainTileset.cpp \
    widgets/room/terrain/TerrainRenderer.cpp \
    widgets/room/terrain/ClassicTerrainRenderer.cpp \
    widgets/room/terrain/TiledTerrainRenderer.cpp \
    network/rest/RestRoomStatus.cpp \
    network/rest/RestConsoleCommand.cpp \
    widgets/ToolboxWidget.cpp \
    widgets/room/renderers/EntityRenderer.cpp \
    widgets/room/renderers/SpawnRenderer.cpp \
    widgets/room/renderers/ExtensionRenderer.cpp \
    widgets/room/renderers/CreepRenderer.cpp \
    widgets/room/renderers/UnknownRenderer.cpp \
    widgets/room/renderers/MineralRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemTombstone.cpp \
    widgets/room/renderers/TombstoneRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemTower.cpp \
    widgets/room/renderers/TowerRenderer.cpp \
    widgets/room/entities/GraphicsItemEnergyBeam.cpp \
    widgets/InvasionWidget.cpp \
    widgets/room/renderers/SourceRenderer.cpp \
    widgets/room/renderers/ConstructionSiteRenderer.cpp \
    widgets/room/entities/GraphicsItemGlow.cpp \
    widgets/room/entities/RoomGraphicsItemStorage.cpp \
    widgets/room/renderers/StorageRenderer.cpp \
    network/rest/RestAuthentication.cpp \
    models/room/RoomEntityModel.cpp \
    models/room/RoomUtils.cpp \
    widgets/room/entities/RoomGraphicsItemRoad.cpp \
    widgets/room/renderers/RoadRenderer.cpp \
    widgets/room/renderers/ControllerRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemContainer.cpp \
    widgets/room/renderers/ContainerRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemExtractor.cpp \
    widgets/room/renderers/ExtractorRenderer.cpp \
    models/room/RoomEntity.cpp \
    widgets/room/entities/RoomGraphicsItemLink.cpp \
    widgets/room/renderers/LinkRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemEnergy.cpp \
    widgets/room/renderers/EnergyRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemTerminal.cpp \
    widgets/room/renderers/TerminalRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemLab.cpp \
    widgets/room/renderers/LabRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemNuker.cpp \
    widgets/room/renderers/NukerRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemRampart.cpp \
    widgets/room/renderers/RampartRenderer.cpp \
    utils/PaintUtils.cpp \
    widgets/room/renderers/WallRenderer.cpp \
    models/world/WorldModel.cpp \
    network/rest/GameInfo.cpp \
    widgets/room/entities/RoomGraphicsItemPowerSpawn.cpp \
    widgets/room/renderers/PowerSpawnRenderer.cpp \
    widgets/room/entities/RoomGraphicsItemObserver.cpp \
    widgets/room/renderers/ObserverRenderer.cpp

HEADERS += \
        MainWindow.h \
    models/room/RoomModel.h \
    models/room/RoomTerrainModel.h \
    ScreepStudioApplication.h \
    models/room/StorageRoomEntity.h \
    utils/JSONUtils.h \
    network/rest/RESTRoomOverview.h \
    network/rest/Badge.h \
    widgets/PropertiesWidget.h \
    widgets/ConsoleWidget.h \
    network/socket/SocketCommandAuth.h \
    network/socket/SocketCommandSubscribe.h \
    models/console/ConsoleModel.h \
    models/server/ServerInfoModel.h \
    models/NetworkModel.h \
    network/RestNetworkManager.h \
    network/SocketNetworkManager.h \
    network/rest/RestServerInfo.h \
    network/rest/RestUserInfo.h \
    models/user/UserInfoModel.h \
    network/socket/SocketEventConsole.h \
    network/socket/SocketEventUser.h \
    network/socket/SocketEventRoom.h \
    network/rest/RestRoomTerrain.h \
    widgets/room/RoomGraphicsView.h \
    widgets/room/RoomGraphicsScene.h \
    widgets/room/entities/RoomGraphicsItem.h \
    widgets/room/entities/RoomGraphicsItemCreep.h \
    widgets/room/entities/RoomGraphicsItemConstructionSite.h \
    widgets/room/entities/RoomGraphicsItemSource.h \
    widgets/room/entities/RoomGraphicsItemUnknown.h \
    widgets/room/entities/RoomGraphicsItemSpawn.h \
    widgets/room/entities/RoomGraphicsItemController.h \
    widgets/room/entities/RoomGraphicsItemMineral.h \
    widgets/room/entities/RoomGraphicsItemExtension.h \
    Preferences.h \
    models/room/StateMachineOpen.h \
    utils/JSONTreeModel.h \
    widgets/InspectorWidget.h \
    widgets/room/entities/RoomGraphicsItemWall.h \
    widgets/CreepViewWidget.h \
    ScreepsApi.h \
    widgets/room/entities/GraphicsItemSelection.h \
    widgets/room/utils/Tileset.h \
    widgets/room/utils/TerrainTileset.h \
    widgets/room/terrain/TerrainRenderer.h \
    widgets/room/terrain/ClassicTerrainRenderer.h \
    widgets/room/terrain/TiledTerrainRenderer.h \
    network/rest/RestRoomStatus.h \
    network/rest/RestConsoleCommand.h \
    widgets/ToolboxWidget.h \
    widgets/room/renderers/EntityRenderer.h \
    widgets/room/renderers/SpawnRenderer.h \
    widgets/room/renderers/ExtensionRenderer.h \
    widgets/room/renderers/CreepRenderer.h \
    widgets/room/renderers/UnknownRenderer.h \
    widgets/room/renderers/MineralRenderer.h \
    widgets/room/entities/RoomGraphicsItemTombstone.h \
    widgets/room/renderers/TombstoneRenderer.h \
    widgets/room/entities/RoomGraphicsItemTower.h \
    widgets/room/renderers/TowerRenderer.h \
    widgets/room/entities/GraphicsItemEnergyBeam.h \
    widgets/InvasionWidget.h \
    widgets/room/renderers/SourceRenderer.h \
    widgets/room/renderers/ConstructionSiteRenderer.h \
    widgets/room/entities/GraphicsItemGlow.h \
    widgets/room/entities/RoomGraphicsItemStorage.h \
    widgets/room/renderers/StorageRenderer.h \
    network/rest/RestAuthentication.h \
    models/room/RoomEntityModel.h \
    models/room/RoomUtils.h \
    widgets/room/entities/RoomGraphicsItemRoad.h \
    widgets/room/renderers/RoadRenderer.h \
    widgets/room/renderers/ControllerRenderer.h \
    widgets/room/entities/RoomGraphicsItemContainer.h \
    widgets/room/renderers/ContainerRenderer.h \
    widgets/room/entities/RoomGraphicsItemExtractor.h \
    widgets/room/renderers/ExtractorRenderer.h \
    models/room/RoomEntity.h \
    widgets/room/entities/RoomGraphicsItemLink.h \
    widgets/room/renderers/LinkRenderer.h \
    widgets/room/entities/RoomGraphicsItemEnergy.h \
    widgets/room/renderers/EnergyRenderer.h \
    widgets/room/entities/RoomGraphicsItemTerminal.h \
    widgets/room/renderers/TerminalRenderer.h \
    widgets/room/entities/RoomGraphicsItemLab.h \
    widgets/room/renderers/LabRenderer.h \
    widgets/room/entities/RoomGraphicsItemNuker.h \
    widgets/room/renderers/NukerRenderer.h \
    widgets/room/entities/RoomGraphicsItemRampart.h \
    widgets/room/renderers/RampartRenderer.h \
    utils/PaintUtils.h \
    widgets/room/renderers/WallRenderer.h \
    models/world/WorldModel.h \
    network/rest/GameInfo.h \
    widgets/room/entities/RoomGraphicsItemPowerSpawn.h \
    widgets/room/renderers/PowerSpawnRenderer.h \
    widgets/room/entities/RoomGraphicsItemObserver.h \
    widgets/room/renderers/ObserverRenderer.h

FORMS += \
        MainWindow.ui \
	widgets/PropertiesWidget.ui \
    	widgets/ConsoleWidget.ui \
    widgets/InspectorWidget.ui \
    widgets/ToolboxWidget.ui \
    widgets/InvasionWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
