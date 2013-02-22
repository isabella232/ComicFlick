import QtQuick 2.0
import Ubuntu.Components 0.1

Rectangle {
    id: root
    width: 360
    height: 360
    focus: true
    Image {
        id: comicImage
        source: "image://comicimageprovider/current"
        Behavior on x {
            PropertyAnimation {
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on y {
            PropertyAnimation {
                easing.type: Easing.InOutQuad
            }
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
        var rect = comic.currentRect()
        comicImage.x = (root.width  / 2) - (rect.x + rect.width / 2)
        comicImage.y = (root.height / 2) - (rect.y + rect.height / 2)
    }
}
