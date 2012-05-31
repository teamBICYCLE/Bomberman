TEMPLATE = app
CONFIG += console
QT += network
CONFIG += crypto
CONFIG += kqoauth

OBJECTS_DIR = ./objs/

SOURCES += \
    srcs/core/Online.cpp \
    srcs/core/Packet.cpp \
    srcs/core/Select.cpp \
    srcs/core/Vector3d.cpp \
    srcs/core/StatesManager.cpp \
    srcs/core/SaveHandler.cpp \
    srcs/core/Map.cpp \
    srcs/core/KeysConfig.cpp \
    srcs/core/BoundingBox.cpp \
    srcs/core/APowerup.cpp \
    srcs/core/AObject.cpp \
    srcs/core/AGameState.cpp \
    srcs/core/PracticalSocket.cpp \
    srcs/game/VelocityPowerup.cpp \
    srcs/game/RangePowerup.cpp \
    srcs/game/PowerupFactory.cpp \
    srcs/game/Player.cpp \
    srcs/game/Monster.cpp \
    srcs/game/MinePowerup.cpp \
    srcs/game/Mine.cpp \
    srcs/game/GhostBoundingBox.cpp \
    srcs/game/Ghost.cpp \
    srcs/game/Explosion.cpp \
    srcs/game/Character.cpp \
    srcs/game/Brick.cpp \
    srcs/game/Bomb.cpp \
    srcs/game/Block.cpp \
    srcs/game/FireBlock.cpp \
    srcs/game/AmmoPowerup.cpp \
    srcs/game/KickPowerup.cpp \
    srcs/graphics/ModelHandler.cpp \
    srcs/graphics/flatTexture.cpp \
    srcs/graphics/Camera.cpp \
    srcs/ia/VirtualMachine.cpp \
    srcs/ia/DangerMap.cpp \
    srcs/ia/This.cpp \
    srcs/ia/Script.cpp \
    srcs/ia/RestoreStack.cpp \
    srcs/ia/LoadScript.cpp \
    srcs/ia/Failure.cpp \
    srcs/ia/Debugger.cpp \
    srcs/ia/Brain.cpp \
    srcs/states/PlayState.cpp \
    srcs/states/AdventureState.cpp \
    srcs/states/ServerState.cpp \
    srcs/states/ClientState.cpp \
    srcs/states/Menu/MenuState.cpp \
    srcs/states/Menu/MenuLine.cpp \
    srcs/states/Menu/MenuEntry.cpp \
    srcs/states/IntroState.cpp \
    srcs/main.cpp \
    srcs/states/Menu/StartGame.cpp \
    srcs/states/Menu/Quit.cpp \
    srcs/states/Menu/QuickStart.cpp \
    srcs/graphics/AModel.cpp \
    srcs/graphics/TexturedCube.cpp \
    srcs/graphics/gdlModel.cpp \
    srcs/graphics/RotatingImg.cpp \
    srcs/graphics/ExplosionBlock.cpp \
    srcs/states/Carrousel/CarrouselHandler.cpp \
    srcs/states/Carrousel/APage.cpp \
    srcs/states/Carrousel/launchGame.cpp \
    srcs/states/Carrousel/AContent.cpp \
    srcs/states/Carrousel/ItemList.cpp \
    srcs/states/Carrousel/AButton.cpp \
    srcs/core/TwitterConnection.cpp \
    srcs/states/Carrousel/LoadContent.cpp \
    srcs/states/Carrousel/QuickGame.cpp \
    srcs/core/Score.cpp

QMAKE_CXXFLAGS += -std=c++0x -W -Wall -Wextra -ggdb

INCLUDEPATH += ./srcs/core/ ./srcs/game/ ./srcs/ia/ ./srcs/graphics/ ./srcs/states/ ./libs

LIBS	+= -L libs -lgdl_gl -lkqoauth -lGL -lGLU -llua -ldl -Wl,--rpath=./libs


HEADERS += \
    srcs/core/Online.hh \
    srcs/core/Packet.hh \
    srcs/core/Select.hh \
    srcs/core/Vector3d.hh \
    srcs/core/StatesManager.hh \
    srcs/core/SaveHandler.hh \
    srcs/core/Map.hh \
    srcs/core/KeysConfig.hh \
    srcs/core/BoundingBox.hh \
    srcs/core/APowerup.hh \
    srcs/core/AObject.hh \
    srcs/core/AGameState.hh \
    srcs/core/PracticalSocket.h \
    srcs/game/VelocityPowerup.hh \
    srcs/game/RangePowerup.hh \
    srcs/game/PowerupFactory.hh \
    srcs/game/Player.hh \
    srcs/game/Monster.hh \
    srcs/game/MinePowerup.hh \
    srcs/game/Mine.hh \
    srcs/game/GhostBoundingBox.hh \
    srcs/game/Ghost.hh \
    srcs/game/Explosion.hh \
    srcs/game/Character.hh \
    srcs/game/Brick.hh \
    srcs/game/Bomb.hh \
    srcs/game/Block.hh \
    srcs/game/FireBlock.hh \
    srcs/game/AmmoPowerup.hh \
    srcs/game/KickPowerup.hh \
    srcs/graphics/ModelHandler.hh \
    srcs/graphics/flatTexture.hh \
    srcs/graphics/Camera.hh \
    srcs/ia/VirtualMachine.hh \
    srcs/ia/DangerMap.hh \
    srcs/ia/This.hh \
    srcs/ia/Script.hh \
    srcs/ia/RestoreStack.hh \
    srcs/ia/luainc.hh \
    srcs/ia/LoadScript.hh \
    srcs/ia/Failure.hh \
    srcs/ia/Brain.hh \
    srcs/states/PlayState.hh \
    srcs/states/AdventureState.hh \
    srcs/states/ServerState.hh \
    srcs/states/ClientState.hh \
    srcs/states/Menu/MenuState.hh \
    srcs/states/Menu/MenuLine.hh \
    srcs/states/Menu/MenuEntry.hh \
    srcs/states/IntroState.hh \
    srcs/states/Menu/StartGame.hh \
    srcs/states/Menu/Quit.hh \
    srcs/states/Menu/QuickStart.hh \
    srcs/graphics/AModel.hh \
    srcs/graphics/TexturedCube.hh \
    srcs/graphics/gdlModel.hh \
    srcs/graphics/RotatingImg.hh \
    srcs/graphics/ExplosionBlock.hh \
    srcs/states/Carrousel/CarrouselHandler.hh \
    srcs/states/Carrousel/APage.hh \
    srcs/states/Carrousel/launchGame.hh \
    srcs/states/Carrousel/AContent.hh \
    srcs/states/Carrousel/ItemList.hh \
    srcs/states/Carrousel/AButton.hh \
    srcs/core/TwitterConnection.hh \
    srcs/states/Carrousel/LoadContent.hh \
    srcs/states/Carrousel/QuickGame.hh \
    srcs/core/Score.hh

MOC_DIR = ./srcs/core/
