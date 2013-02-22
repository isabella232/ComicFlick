TEMPLATE = subdirs
SUBDIRS = comicflick qt-gui opencv-squares \
    quick
opencv-squares.depends = comicflick
qt-gui.depends = comicflick
quick.depends = comicflick

QMAKE_CXXFLAGS += -std=c++0x
