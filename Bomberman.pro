TEMPLATE = app
CONFIG += console
CONFIG -= qt

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

CXXFLAGS += -W -Wall -Wextra
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
