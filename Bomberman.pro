TEMPLATE = app
CONFIG += console
QT -= gui

SOURCES += \
    srcs/core/Vector3d.cpp \
    srcs/core/StatesManager.cpp \
    srcs/core/SaveHandler.cpp \
    srcs/core/Map.cpp \
    srcs/core/KeysConfig.cpp \
    srcs/core/BoundingBox.cpp \
    srcs/core/APowerup.cpp \
    srcs/core/AObject.cpp \
    srcs/core/AGameState.cpp \
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
    srcs/game/AmmoPowerup.cpp \
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
    srcs/states/MenuState.cpp \
    srcs/states/MenuLine.cpp \
    srcs/states/MenuEntry.cpp \
    srcs/states/IntroState.cpp \
    srcs/main.cpp

QMAKE_CXXFLAGS += -std=c++0x -W -Wall -Wextra

INCLUDEPATH += -I ./srcs/core/ -I ./srcs/game/ -I ./srcs/ia/ -I ./srcs/graphics/ -I ./srcs/states/


LIBS	+= -lgdl_gl -lGL -lGLU -llua
HEADERS += \ 
    srcs/core/Vector3d.hh \
    srcs/core/StatesManager.hh \
    srcs/core/SaveHandler.hh \
    srcs/core/Map.hh \
    srcs/core/KeysConfig.hh \
    srcs/core/BoundingBox.hh \
    srcs/core/APowerup.hh \
    srcs/core/AObject.hh \
    srcs/core/AGameState.hh \
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
    srcs/game/AmmoPowerup.hh \
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
    srcs/states/MenuState.hh \
    srcs/states/MenuLine.hh \
    srcs/states/MenuEntry.hh \
    srcs/states/IntroState.hh
