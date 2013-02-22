##-------------------------------------------------
##
## Project created by QtCreator 2013-02-08T13:57:27
##
##-------------------------------------------------

include( "../super.pri" )
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = qt-gui
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    += MainWindow.ui

LIBS += -L$$BUILD/comicflick -lcomicflick
INCLUDEPATH += $$SRC/comicflick
DEPENDPATH += $$SRC/comicflick

PRE_TARGETDEPS += $$BUILD/comicflick/libcomicflick.a

CONFIG += link_pkgconfig
PKGCONFIG += opencv

OTHER_FILES += \
    why_are_you_reading_this.png

for(file, OTHER_FILES) {
    QMAKE_POST_LINK += "cp $$SRC/$$TARGET/$$file $$BUILD/$$TARGET"
}
