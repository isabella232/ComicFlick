import QtQuick 2.0
import Ubuntu.Components 0.1
import "helpers.js" as My

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
                page: Flickable {
                    anchors {
                        margins: units.gu(1)
                        fill: parent
                    }
                    visible: false
                    contentWidth: grid.width
                    contentHeight: grid.height
                    Grid {
                        id: grid
                        columns: 3
                        spacing: units.gu(1)
                        UbuntuShape {
                            radius: "medium"
                            width: units.gu(12)
                            height: units.gu(12)
                            color: My.color.ubuntuOrange
                            MouseArea {
                                anchors.fill: parent
                                onClicked: pageStack.push(comicPage)
                            }
                        }
                        Repeater {
                            model: 17
                            UbuntuShape {
                                radius: "medium"
                                width: units.gu(12)
                                height: units.gu(12)
                                color: {
                                    var keys = Object.keys(My.color);
                                    var i = Math.floor( Math.random()*keys.length );
                                    return My.color[keys[i]];
                                }
                            }
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
