import QtQuick 2.0
import Ubuntu.Components 0.1

Item {
    anchors.fill: parent
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
        Connections {
            target: comic
            onChanged: comicImage.updatePosition()
        }
        Component.onCompleted: updatePosition()
        function updatePosition() {
            var rect = comic.currentRect()
            comicImage.x = (root.width  / 2) - (rect.x + rect.width / 2)
            comicImage.y = (root.height / 2) - (rect.y + rect.height / 2)
        }
    }
}
