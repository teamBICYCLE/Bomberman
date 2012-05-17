TEMPLATE = app
CONFIG += console
QT -= gui

SOURCES += main.cpp \
    StatesManager.cpp \
    AGameState.cpp \
    IntroState.cpp \
    PlayState.cpp \
    AObject.cpp \
    Vector3d.cpp \
    Block.cpp \
    Brick.cpp \
    APowerup.cpp \
    PowerupFactory.cpp \
    RangePowerup.cpp \
    VelocityPowerup.cpp \
    AmmoPowerup.cpp \
    Player.cpp \
    Map.cpp \
    Camera.cpp \
    Bomb.cpp \
    BoundingBox.cpp \
    GhostBoundingBox.cpp \
    Character.cpp \
    Explosion.cpp \
    Monster.cpp \
    Ghost.cpp \
    SaveHandler.cpp \
    ia/VirtualMachine.cpp \
    ia/Debugger.cpp \
    ia/Script.cpp \
    ia/RestoreStack.cpp \
    ia/This.cpp \
    ia/LoadScript.cpp \
    ia/Failure.cpp \
    ia/Brain.cpp \
    KeysConfig.cpp

QMAKE_CXXFLAGS += -std=c++0x -W -Wall -Wextra

LIBS	+= -lgdl_gl -lGL -lGLU -L./ia/liblua/ -llua-5.1

HEADERS += \
    StatesManager.hh \
    AGameState.hh \
    IntroState.hh \
    PlayState.hh \
    AObject.hh \
    Vector3d.hh \
    Block.hh \
    Brick.hh \
    APowerup.hh \
    PowerupFactory.hh \
    RangePowerup.hh \
    VelocityPowerup.hh \
    AmmoPowerup.hh \
    Player.hh \
    Map.hh \
    Camera.hh \
    Bomb.hh \
    BoundingBox.hh \
    GhostBoundingBox.hh \
    Character.hh \
    Explosion.hh \
    Monster.hh \
    Ghost.hh \
    SaveHandler.hh \
    ia/luainc.hh \
    ia/VirtualMachine.hh \
    ia/Debugger.hh \
    ia/Script.hh \
    ia/LoadScript.hh \
    ia/Failure.hh \
    ia/Brain.hh \
    KeysConfig.hh
