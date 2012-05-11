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
    Character.cpp \
    Explosion.cpp

QMAKE_CXXFLAGS += -std=c++0x -W -Wall -Wextra

LIBS	+= -lgdl_gl -lGL -lGLU

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
    Character.hh \
    Explosion.hh
