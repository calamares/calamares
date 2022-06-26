include(../common.pri)

TEMPLATE = lib
TARGET = kdsingleapplication
QT = core network
CONFIG += static

SOURCES += \
    kdsingleapplication.cpp \
    kdsingleapplication_localsocket.cpp \

HEADERS += \
    kdsingleapplication.h \
    kdsingleapplication_lib.h \
    kdsingleapplication_localsocket_p.h \

DEFINES += \
    KDSINGLEAPPLICATION_BUILD

win32:LIBS += -lkernel32
