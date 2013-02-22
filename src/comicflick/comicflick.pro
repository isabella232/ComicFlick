#-------------------------------------------------
#
# Project created by QtCreator 2013-02-08T13:23:07
#
#-------------------------------------------------

include(../super.pri)

TARGET = comicflick
TEMPLATE = lib
CONFIG += staticlib

SOURCES += comicflick.cpp \
    ComicFrame.cpp

HEADERS += comicflick.h \
    ComicFrame.h

QMAKE_CXXFLAGS += -std=c++0x

CONFIG += link_pkgconfig
PKGCONFIG += opencv
