#-------------------------------------------------
#
# Project created by QtCreator 2013-02-08T13:23:07
#
#-------------------------------------------------

TARGET = comicflick
TEMPLATE = lib
CONFIG += staticlib

SOURCES += comicflick.cpp

HEADERS += comicflick.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

QMAKE_CXXFLAGS += -std=c++0x

CONFIG += link_pkgconfig
PKGCONFIG += opencv
