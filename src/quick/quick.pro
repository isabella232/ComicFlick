include( "../super.pri" )
# Add more folders to ship with the application, here
folder_01.source = qml/quick
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

LIBS += -L$$BUILD/comicflick -lcomicflick
INCLUDEPATH += $$SRC/comicflick
DEPENDPATH += $$SRC/comicflick
PRE_TARGETDEPS += $$BUILD/comicflick/libcomicflick.a
QMAKE_CXXFLAGS += -std=c++0x
CONFIG += link_pkgconfig
PKGCONFIG += opencv

OTHER_FILES += \
    qml/quick/helpers.js \
    qml/quick/SmoothProperty.qml \
    qml/quick/ComicsPageItem.qml \
    why_are_you_reading_this.png

for(file, OTHER_FILES) {
    QMAKE_POST_LINK += "cp $$SRC/$$TARGET/$$file $$BUILD/$$TARGET;"
}
