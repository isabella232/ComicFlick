import QtQuick 2.0
import Ubuntu.Components 0.1

Item {
    id: root
    anchors.fill: parent
    property bool zoom: true
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
        Behavior on width {
            PropertyAnimation {
                easing.type: Easing.InOutQuad
            }
        }
        Behavior on height {
            PropertyAnimation {
                easing.type: Easing.InOutQuad
            }
        }
        Connections {
            target: comic
            onChanged: comicImage.updatePosition()
        }
        Component.onCompleted: {
            updatePosition()
        }
        function updatePosition() {
            var rect  = comic.currentRect();
            var rootRatio = root.width / root.height;
            var rectRatio = rect.width / rect.height;
            var ratio = !zoom ? 1 : rectRatio > rootRatio?
                root.width  / rect.width :
                root.height / rect.height;
            comicImage.x = (root.width  / 2) - (rect.x + rect.width  / 2) * ratio;
            comicImage.y = (root.height / 2) - (rect.y + rect.height / 2) * ratio;
            comicImage.width  = implicitWidth  * ratio;
            comicImage.height = implicitHeight * ratio;
        }
    }
}
