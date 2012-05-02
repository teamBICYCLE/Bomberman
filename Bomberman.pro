TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    StatesManager.cpp \
    AGameState.cpp \
    IntroState.cpp
CXXFLAGS += -W -Wall -Wextra
LIBS	+= -lgdl_gl -lGL -lGLU

HEADERS += \
    StatesManager.hh \
    AGameState.hh \
    IntroState.hh
