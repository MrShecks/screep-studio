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
    ui/dialogs/ConnectDialog.cpp \
    utils/JSONUtils.cpp \
    network/rest/RESTRoomOverview.cpp \
    network/rest/Badge.cpp \
    ui/widgets/PropertiesWidget.cpp \
    ui/widgets/ConsoleWidget.cpp \
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
    ui/widgets/room/RoomGraphicsView.cpp \
    ui/widgets/room/RoomGraphicsScene.cpp \
    ui/widgets/room/entities/RoomGraphicsItem.cpp \
    ui/widgets/room/entities/RoomGraphicsItemCreep.cpp \
    ui/widgets/room/entities/RoomGraphicsItemConstructionSite.cpp \
    ui/widgets/room/entities/RoomGraphicsItemSource.cpp \
    ui/widgets/room/entities/RoomGraphicsItemUnknown.cpp \
    ui/widgets/room/entities/RoomGraphicsItemSpawn.cpp \
    ui/widgets/room/entities/RoomGraphicsItemController.cpp \
    ui/widgets/room/entities/RoomGraphicsItemMineral.cpp \
    ui/widgets/room/entities/RoomGraphicsItemExtension.cpp \
    Preferences.cpp \
    models/room/StateMachineOpen.cpp \
    utils/JSONTreeModel.cpp \
    ui/widgets/InspectorWidget.cpp \
    ui/widgets/room/entities/RoomGraphicsItemWall.cpp \
    ui/widgets/CreepViewWidget.cpp \
    ScreepsApi.cpp \
    ui/widgets/room/entities/GraphicsItemSelection.cpp \
    ui/widgets/room/utils/Tileset.cpp \
    ui/widgets/room/utils/TerrainTileset.cpp \
    ui/widgets/room/terrain/TerrainRenderer.cpp \
    ui/widgets/room/terrain/ClassicTerrainRenderer.cpp \
    ui/widgets/room/terrain/TiledTerrainRenderer.cpp \
    network/rest/RestRoomStatus.cpp \
    network/rest/RestConsoleCommand.cpp \
    ui/widgets/ToolboxWidget.cpp \
    ui/widgets/room/renderers/EntityRenderer.cpp \
    ui/widgets/room/renderers/SpawnRenderer.cpp \
    ui/widgets/room/renderers/ExtensionRenderer.cpp \
    ui/widgets/room/renderers/CreepRenderer.cpp \
    ui/widgets/room/renderers/UnknownRenderer.cpp \
    ui/widgets/room/renderers/MineralRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemTombstone.cpp \
    ui/widgets/room/renderers/TombstoneRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemTower.cpp \
    ui/widgets/room/renderers/TowerRenderer.cpp \
    ui/widgets/room/entities/GraphicsItemEnergyBeam.cpp \
    ui/widgets/InvasionWidget.cpp \
    ui/widgets/room/renderers/SourceRenderer.cpp \
    ui/widgets/room/renderers/ConstructionSiteRenderer.cpp \
    ui/widgets/room/entities/GraphicsItemGlow.cpp \
    ui/widgets/room/entities/RoomGraphicsItemStorage.cpp \
    ui/widgets/room/renderers/StorageRenderer.cpp \
    network/rest/RestAuthentication.cpp \
    models/room/RoomEntityModel.cpp \
    models/room/RoomUtils.cpp \
    ui/widgets/room/entities/RoomGraphicsItemRoad.cpp \
    ui/widgets/room/renderers/RoadRenderer.cpp \
    ui/widgets/room/renderers/ControllerRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemContainer.cpp \
    ui/widgets/room/renderers/ContainerRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemExtractor.cpp \
    ui/widgets/room/renderers/ExtractorRenderer.cpp \
    models/room/RoomEntity.cpp \
    ui/widgets/room/entities/RoomGraphicsItemLink.cpp \
    ui/widgets/room/renderers/LinkRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemEnergy.cpp \
    ui/widgets/room/renderers/EnergyRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemTerminal.cpp \
    ui/widgets/room/renderers/TerminalRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemLab.cpp \
    ui/widgets/room/renderers/LabRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemNuker.cpp \
    ui/widgets/room/renderers/NukerRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemRampart.cpp \
    ui/widgets/room/renderers/RampartRenderer.cpp \
    utils/PaintUtils.cpp \
    ui/widgets/room/renderers/WallRenderer.cpp \
    models/world/WorldModel.cpp \
    network/rest/GameInfo.cpp \
    ui/widgets/room/entities/RoomGraphicsItemPowerSpawn.cpp \
    ui/widgets/room/renderers/PowerSpawnRenderer.cpp \
    ui/widgets/room/entities/RoomGraphicsItemObserver.cpp \
    ui/widgets/room/renderers/ObserverRenderer.cpp

HEADERS += \
        MainWindow.h \
    models/room/RoomModel.h \
    models/room/RoomTerrainModel.h \
    ScreepStudioApplication.h \
    models/room/StorageRoomEntity.h \
    ui/dialogs/ConnectDialog.h \
    utils/JSONUtils.h \
    network/rest/RESTRoomOverview.h \
    network/rest/Badge.h \
    ui/widgets/PropertiesWidget.h \
    ui/widgets/ConsoleWidget.h \
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
    ui/widgets/room/RoomGraphicsView.h \
    ui/widgets/room/RoomGraphicsScene.h \
    ui/widgets/room/entities/RoomGraphicsItem.h \
    ui/widgets/room/entities/RoomGraphicsItemCreep.h \
    ui/widgets/room/entities/RoomGraphicsItemConstructionSite.h \
    ui/widgets/room/entities/RoomGraphicsItemSource.h \
    ui/widgets/room/entities/RoomGraphicsItemUnknown.h \
    ui/widgets/room/entities/RoomGraphicsItemSpawn.h \
    ui/widgets/room/entities/RoomGraphicsItemController.h \
    ui/widgets/room/entities/RoomGraphicsItemMineral.h \
    ui/widgets/room/entities/RoomGraphicsItemExtension.h \
    Preferences.h \
    models/room/StateMachineOpen.h \
    utils/JSONTreeModel.h \
    ui/widgets/InspectorWidget.h \
    ui/widgets/room/entities/RoomGraphicsItemWall.h \
    ui/widgets/CreepViewWidget.h \
    ScreepsApi.h \
    ui/widgets/room/entities/GraphicsItemSelection.h \
    ui/widgets/room/utils/Tileset.h \
    ui/widgets/room/utils/TerrainTileset.h \
    ui/widgets/room/terrain/TerrainRenderer.h \
    ui/widgets/room/terrain/ClassicTerrainRenderer.h \
    ui/widgets/room/terrain/TiledTerrainRenderer.h \
    network/rest/RestRoomStatus.h \
    network/rest/RestConsoleCommand.h \
    ui/widgets/ToolboxWidget.h \
    ui/widgets/room/renderers/EntityRenderer.h \
    ui/widgets/room/renderers/SpawnRenderer.h \
    ui/widgets/room/renderers/ExtensionRenderer.h \
    ui/widgets/room/renderers/CreepRenderer.h \
    ui/widgets/room/renderers/UnknownRenderer.h \
    ui/widgets/room/renderers/MineralRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemTombstone.h \
    ui/widgets/room/renderers/TombstoneRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemTower.h \
    ui/widgets/room/renderers/TowerRenderer.h \
    ui/widgets/room/entities/GraphicsItemEnergyBeam.h \
    ui/widgets/InvasionWidget.h \
    ui/widgets/room/renderers/SourceRenderer.h \
    ui/widgets/room/renderers/ConstructionSiteRenderer.h \
    ui/widgets/room/entities/GraphicsItemGlow.h \
    ui/widgets/room/entities/RoomGraphicsItemStorage.h \
    ui/widgets/room/renderers/StorageRenderer.h \
    network/rest/RestAuthentication.h \
    models/room/RoomEntityModel.h \
    models/room/RoomUtils.h \
    ui/widgets/room/entities/RoomGraphicsItemRoad.h \
    ui/widgets/room/renderers/RoadRenderer.h \
    ui/widgets/room/renderers/ControllerRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemContainer.h \
    ui/widgets/room/renderers/ContainerRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemExtractor.h \
    ui/widgets/room/renderers/ExtractorRenderer.h \
    models/room/RoomEntity.h \
    ui/widgets/room/entities/RoomGraphicsItemLink.h \
    ui/widgets/room/renderers/LinkRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemEnergy.h \
    ui/widgets/room/renderers/EnergyRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemTerminal.h \
    ui/widgets/room/renderers/TerminalRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemLab.h \
    ui/widgets/room/renderers/LabRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemNuker.h \
    ui/widgets/room/renderers/NukerRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemRampart.h \
    ui/widgets/room/renderers/RampartRenderer.h \
    utils/PaintUtils.h \
    ui/widgets/room/renderers/WallRenderer.h \
    models/world/WorldModel.h \
    network/rest/GameInfo.h \
    ui/widgets/room/entities/RoomGraphicsItemPowerSpawn.h \
    ui/widgets/room/renderers/PowerSpawnRenderer.h \
    ui/widgets/room/entities/RoomGraphicsItemObserver.h \
    ui/widgets/room/renderers/ObserverRenderer.h

FORMS += \
        MainWindow.ui \
    ui/dialogs/ConnectDialog.ui \
	ui/widgets/PropertiesWidget.ui \
    	ui/widgets/ConsoleWidget.ui \
    ui/widgets/InspectorWidget.ui \
    ui/widgets/ToolboxWidget.ui \
    ui/widgets/InvasionWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
