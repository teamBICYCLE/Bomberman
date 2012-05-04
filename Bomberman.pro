CONFIG -= qt
CONFIG += console
TEMPLATE = app
CXXFLAGS += -W -Wall -Wextra -Werror -std=c++0x
LIBS += -lgdl_gl -lGL -lGLU

HEADERS += \
    VelocityPowerup.hh \
    Vector3d.hh \
    StatesManager.hh \
    RangePowerup.hh \
    PowerupFactory.hh \
    PlayState.hh \
    Player.hh \
    IntroState.hh \
    ICase.hpp \
    Brick.hh \
    Block.hh \
    APowerup.hh \
    AObject.hh \
    AmmoPowerup.hh \
    AGameState.hh \
    Map.hh

SOURCES += \
    VelocityPowerup.cpp \
    Vector3d.cpp \
    StatesManager.cpp \
    RangePowerup.cpp \
    PowerupFactory.cpp \
    PlayState.cpp \
    Player.cpp \
    main.cpp \
    IntroState.cpp \
    Brick.cpp \
    Block.cpp \
    APowerup.cpp \
    AObject.cpp \
    AmmoPowerup.cpp \
    AGameState.cpp \
    Map.cpp
