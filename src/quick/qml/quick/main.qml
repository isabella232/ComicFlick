import QtQuick 2.0
import Ubuntu.Components 0.1

MainView {
    id: root
    width: units.gu(40)  // magic numbers
    height: units.gu(71) // taken from lp:gallery-app for phone size
    focus: true
    PageStack {
        id: pageStack
        anchors.fill: parent
        Component.onCompleted: {
            push(mainPage);
            // TODO http://askubuntu.com/questions/260782
            if ("headerVisible" in pageStack)
                headerVisible = false;
        }
        Tabs {
            id: mainPage
            anchors.fill: parent
            Tab {
                title: "ComicFlick"
                page: Page {
                    anchors.fill: parent;
                    visible: false
                    Rectangle {
                        anchors.fill: parent;
                        color: "#ffffaa"
                        MouseArea {
                            anchors.fill: parent;
                            onClicked: pageStack.push(comicPage)
                        }
                    }
                }
            }
        }
        Comic {
            id: comicPage
            visible: false
        }
    }

    Keys.onPressed: {
        if ([ Qt.Key_Up, Qt.Key_W, Qt.Key_J ].indexOf(event.key) > -1) {
            comic.up();
        }
        if ([ Qt.Key_Down, Qt.Key_S, Qt.Key_K ].indexOf(event.key) > -1) {
            comic.down();
        }
        if ([ Qt.Key_Left , Qt.Key_A, Qt.Key_H ].indexOf(event.key) > -1) {
            comic.left();
        }
        if ([ Qt.Key_Right, Qt.Key_D, Qt.Key_L ].indexOf(event.key) > -1) {
            comic.right();
        }
    }
}
