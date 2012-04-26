TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    GameTest.cpp \
    AObject.cpp \
    Vector3f.cpp
CXXFLAGS += -W -Wall -Wextra
LIBS	+= -lgdl_gl -lGL -lGLU

HEADERS += \
    GameTest.hpp \
    AObject.hpp \
    Vector3f.hpp
