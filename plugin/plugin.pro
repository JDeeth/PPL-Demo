# Shared library without any Qt functionality
TEMPLATE = lib
QT -= gui core

CONFIG += console c++14 warn_on plugin
CONFIG -= thread qt

VERSION = 1.0.0

INCLUDEPATH += ../xplane_sdk/sdk/CHeaders/XPLM
INCLUDEPATH += ../xplane_sdk/sdk/CHeaders/Wrappers
INCLUDEPATH += ../xplane_sdk/sdk/CHeaders/Widgets
INCLUDEPATH += ../ppl/src
INCLUDEPATH += ../ppl/include

DEFINES += XPLM210 XPLM200

win32 {
# This has not been tested.
    DEFINES += APL=0 IBM=1 LIN=0
    LIBS += -L"$$PWD/../../SDK/Libraries/Win"
    LIBS += -lXPLM_64 -lXPWidgets_64
    # LIBS += OpenGL libraries GL and GLEW (?)
    # LIBS += wherever PPL ends up
    TARGET = win.xpl
}

linux {
    DEFINES += APL=0 IBM=0 LIN=1
    LIBS += -L$$OUT_PWD/../ppl/lib
    CONFIG(debug, debug|release) {
        LIBS += -lppld
    } else {
        LIBS += -lppl
    }
    LIBS += -lGL -lGLEW
    TARGET = lin.xpl
    INCLUDEPATH += /usr/include/c++/4.8.4
    QMAKE_CXXFLAGS += -Wall -Wextra -Wfloat-equal -pedantic -Wno-c++11-narrowing
    QMAKE_CXXFLAGS += -fvisibility=hidden -std=c++14
}

macx {
# This has not been tested.
    DEFINES += APL=1 IBM=0 LIN=0
    # LIBS += OpenGL libraries GL and GLEW (?)
    # LIBS += wherever PPL ends up
    TARGET = mac.xpl
    QMAKE_LFLAGS += -flat_namespace -undefined suppress
    CONFIG += x86 ppc
}

HEADERS += \
    flapretractor.h \
    playannoyingsounds.h \
    sendamessage.h

SOURCES += \
    plugin.m.cpp \
    flapretractor.cpp \
    playannoyingsounds.cpp \
    sendamessage.cpp

DISTFILES += \
    README.md
