# Shared library without any Qt functionality
TEMPLATE = lib
QT -= gui core

CONFIG += warn_on plugin release c++14
CONFIG -= thread qt rtti debug

VERSION = 1.0.0

INCLUDEPATH += ../../SDK/CHeaders/XPLM
INCLUDEPATH += ../../SDK/CHeaders/Wrappers
INCLUDEPATH += ../../SDK/CHeaders/Widgets
INCLUDEPATH += ../ppl/src
INCLUDEPATH += ../ppl/include

# Defined to use X-Plane SDK 2.0 capabilities - no backward compatibility before 9.0
DEFINES += XPLM210=1 XPLM200=1

include(../common.pri)

win32 { # Untested!
    DEFINES += APL=0 IBM=1 LIN=0
    LIBS += -L"$$PWD/../../SDK/Libraries/Win"
    LIBS += -lXPLM_64 -lXPWidgets_64
    TARGET = win.xpl
}

unix:!macx {
    DEFINES += APL=0 IBM=0 LIN=1
    LIBS += -L../../../ppl/lib -lppl
    TARGET = lin.xpl
    INCLUDEPATH += /usr/include/c++/4.8.4
    QMAKE_CXXFLAGS += -Wall -Wextra -Wfloat-equal -pedantic -Wno-c++11-narrowing
    QMAKE_CXXFLAGS += -fvisibility=hidden -std=c++14 #-stdlib=libc++
}

macx { # Untested!
    DEFINES += APL=1 IBM=0 LIN=0
    TARGET = mac.xpl
    QMAKE_LFLAGS += -flat_namespace -undefined suppress

    # Build for multiple architectures.
    # The following line is only needed to build universal on PPC architectures.
    # QMAKE_MAC_SDK=/Developer/SDKs/MacOSX10.4u.sdk
    # The following line defines for which architectures we build.
    CONFIG += x86 ppc
}

HEADERS +=

SOURCES += \
    plugin.m.cpp \
