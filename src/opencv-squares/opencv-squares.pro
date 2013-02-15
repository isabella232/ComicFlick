include(../super.pri)
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

SOURCES += main.cpp

QMAKE_CXXFLAGS += -std=c++0x

CONFIG += link_pkgconfig
PKGCONFIG += opencv

LIBS += -L$$BUILD/comicflick/ -lcomicflick
INCLUDEPATH += $$SRC/comicflick
DEPENDPATH += $$SRC/comicflick
PRE_TARGETDEPS += $$BUILD/comicflick/libcomicflick.a
