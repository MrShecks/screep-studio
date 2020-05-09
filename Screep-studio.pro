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
    models/client/ClientModel.cpp \
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
    ui/scenes/room/RoomGraphicsView.cpp \
    ui/scenes/room/RoomGraphicsScene.cpp \
    ui/scenes/room/entities/RoomGraphicsItem.cpp \
    ui/scenes/room/entities/RoomGraphicsItemCreep.cpp \
    ui/scenes/room/entities/RoomGraphicsItemConstructionSite.cpp \
    ui/scenes/room/entities/RoomGraphicsItemSource.cpp \
    ui/scenes/room/entities/RoomGraphicsItemUnknown.cpp \
    ui/scenes/room/entities/RoomGraphicsItemSpawn.cpp \
    ui/scenes/room/entities/RoomGraphicsItemController.cpp \
    ui/scenes/room/entities/RoomGraphicsItemMineral.cpp \
    ui/scenes/room/entities/RoomGraphicsItemExtension.cpp \
    Preferences.cpp \
    models/room/StateMachineOpen.cpp \
    utils/JSONTreeModel.cpp \
    ui/widgets/InspectorWidget.cpp \
    ui/scenes/room/entities/RoomGraphicsItemWall.cpp \
    ui/widgets/CreepViewWidget.cpp \
    ScreepsApi.cpp \
    ui/scenes/room/entities/GraphicsItemSelection.cpp \
    ui/scenes/room/utils/Tileset.cpp \
    ui/scenes/room/utils/TerrainTileset.cpp \
    ui/scenes/room/terrain/TerrainRenderer.cpp \
    ui/scenes/room/terrain/ClassicTerrainRenderer.cpp \
    ui/scenes/room/terrain/TiledTerrainRenderer.cpp \
    network/rest/RestRoomStatus.cpp \
    network/rest/RestConsoleCommand.cpp \
    ui/widgets/ToolboxWidget.cpp \
    ui/scenes/room/renderers/EntityRenderer.cpp \
    ui/scenes/room/renderers/SpawnRenderer.cpp \
    ui/scenes/room/renderers/ExtensionRenderer.cpp \
    ui/scenes/room/renderers/CreepRenderer.cpp \
    ui/scenes/room/renderers/UnknownRenderer.cpp \
    ui/scenes/room/renderers/MineralRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemTombstone.cpp \
    ui/scenes/room/renderers/TombstoneRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemTower.cpp \
    ui/scenes/room/renderers/TowerRenderer.cpp \
    ui/scenes/room/entities/GraphicsItemEnergyBeam.cpp \
    ui/widgets/InvasionWidget.cpp \
    ui/scenes/room/renderers/SourceRenderer.cpp \
    ui/scenes/room/renderers/ConstructionSiteRenderer.cpp \
    ui/scenes/room/entities/GraphicsItemGlow.cpp \
    ui/scenes/room/entities/RoomGraphicsItemStorage.cpp \
    ui/scenes/room/renderers/StorageRenderer.cpp \
    network/rest/RestAuthentication.cpp \
    models/room/RoomEntityModel.cpp \
    models/room/RoomUtils.cpp \
    ui/scenes/room/entities/RoomGraphicsItemRoad.cpp \
    ui/scenes/room/renderers/RoadRenderer.cpp \
    ui/scenes/room/renderers/ControllerRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemContainer.cpp \
    ui/scenes/room/renderers/ContainerRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemExtractor.cpp \
    ui/scenes/room/renderers/ExtractorRenderer.cpp \
    models/room/RoomEntity.cpp \
    ui/scenes/room/entities/RoomGraphicsItemLink.cpp \
    ui/scenes/room/renderers/LinkRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemEnergy.cpp \
    ui/scenes/room/renderers/EnergyRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemTerminal.cpp \
    ui/scenes/room/renderers/TerminalRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemLab.cpp \
    ui/scenes/room/renderers/LabRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemNuker.cpp \
    ui/scenes/room/renderers/NukerRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemRampart.cpp \
    ui/scenes/room/renderers/RampartRenderer.cpp \
    utils/PaintUtils.cpp \
    ui/scenes/room/renderers/WallRenderer.cpp \
    models/world/WorldModel.cpp \
    network/rest/GameInfo.cpp \
    ui/scenes/room/entities/RoomGraphicsItemPowerSpawn.cpp \
    ui/scenes/room/renderers/PowerSpawnRenderer.cpp \
    ui/scenes/room/entities/RoomGraphicsItemObserver.cpp \
    ui/scenes/room/renderers/ObserverRenderer.cpp

HEADERS += \
        MainWindow.h \
    models/client/ClientModel.h \
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
    ui/scenes/room/RoomGraphicsView.h \
    ui/scenes/room/RoomGraphicsScene.h \
    ui/scenes/room/entities/RoomGraphicsItem.h \
    ui/scenes/room/entities/RoomGraphicsItemCreep.h \
    ui/scenes/room/entities/RoomGraphicsItemConstructionSite.h \
    ui/scenes/room/entities/RoomGraphicsItemSource.h \
    ui/scenes/room/entities/RoomGraphicsItemUnknown.h \
    ui/scenes/room/entities/RoomGraphicsItemSpawn.h \
    ui/scenes/room/entities/RoomGraphicsItemController.h \
    ui/scenes/room/entities/RoomGraphicsItemMineral.h \
    ui/scenes/room/entities/RoomGraphicsItemExtension.h \
    Preferences.h \
    models/room/StateMachineOpen.h \
    utils/JSONTreeModel.h \
    ui/widgets/InspectorWidget.h \
    ui/scenes/room/entities/RoomGraphicsItemWall.h \
    ui/widgets/CreepViewWidget.h \
    ScreepsApi.h \
    ui/scenes/room/entities/GraphicsItemSelection.h \
    ui/scenes/room/utils/Tileset.h \
    ui/scenes/room/utils/TerrainTileset.h \
    ui/scenes/room/terrain/TerrainRenderer.h \
    ui/scenes/room/terrain/ClassicTerrainRenderer.h \
    ui/scenes/room/terrain/TiledTerrainRenderer.h \
    network/rest/RestRoomStatus.h \
    network/rest/RestConsoleCommand.h \
    ui/widgets/ToolboxWidget.h \
    ui/scenes/room/renderers/EntityRenderer.h \
    ui/scenes/room/renderers/SpawnRenderer.h \
    ui/scenes/room/renderers/ExtensionRenderer.h \
    ui/scenes/room/renderers/CreepRenderer.h \
    ui/scenes/room/renderers/UnknownRenderer.h \
    ui/scenes/room/renderers/MineralRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemTombstone.h \
    ui/scenes/room/renderers/TombstoneRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemTower.h \
    ui/scenes/room/renderers/TowerRenderer.h \
    ui/scenes/room/entities/GraphicsItemEnergyBeam.h \
    ui/widgets/InvasionWidget.h \
    ui/scenes/room/renderers/SourceRenderer.h \
    ui/scenes/room/renderers/ConstructionSiteRenderer.h \
    ui/scenes/room/entities/GraphicsItemGlow.h \
    ui/scenes/room/entities/RoomGraphicsItemStorage.h \
    ui/scenes/room/renderers/StorageRenderer.h \
    network/rest/RestAuthentication.h \
    models/room/RoomEntityModel.h \
    models/room/RoomUtils.h \
    ui/scenes/room/entities/RoomGraphicsItemRoad.h \
    ui/scenes/room/renderers/RoadRenderer.h \
    ui/scenes/room/renderers/ControllerRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemContainer.h \
    ui/scenes/room/renderers/ContainerRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemExtractor.h \
    ui/scenes/room/renderers/ExtractorRenderer.h \
    models/room/RoomEntity.h \
    ui/scenes/room/entities/RoomGraphicsItemLink.h \
    ui/scenes/room/renderers/LinkRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemEnergy.h \
    ui/scenes/room/renderers/EnergyRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemTerminal.h \
    ui/scenes/room/renderers/TerminalRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemLab.h \
    ui/scenes/room/renderers/LabRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemNuker.h \
    ui/scenes/room/renderers/NukerRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemRampart.h \
    ui/scenes/room/renderers/RampartRenderer.h \
    utils/PaintUtils.h \
    ui/scenes/room/renderers/WallRenderer.h \
    models/world/WorldModel.h \
    network/rest/GameInfo.h \
    ui/scenes/room/entities/RoomGraphicsItemPowerSpawn.h \
    ui/scenes/room/renderers/PowerSpawnRenderer.h \
    ui/scenes/room/entities/RoomGraphicsItemObserver.h \
    ui/scenes/room/renderers/ObserverRenderer.h

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
