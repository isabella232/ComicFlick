import QtQuick 2.0
import Ubuntu.Components 0.1
import 'helpers.js' as My

UbuntuShape {
    id          : shape
    width       : units.gu(12)
    height      : units.gu(12)
    radius      : "medium"
    color       : model.color || My.randomColor()
    signal pressAndHold()
    states      : [
        State {
            name: "expanded"
            AnchorChanges {
                target: shape
                anchors.left: shape.parent.left
                anchors.right: shape.parent.right
            }
            PropertyChanges {
                target: shape
                z: 2
            }
        }
    ]
    transitions: Transition {
        AnchorAnimation   { duration: 100 }
        PropertyAnimation { duration: 100; property: "z" }
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.state = !parent.state ? "expanded" : ""
        onPressAndHold: parent.pressAndHold()
    }
}
