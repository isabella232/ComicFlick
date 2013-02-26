import QtQuick 2.0
import Ubuntu.Components 0.1
import 'helpers.js' as My

Page {
    signal comicSelected(string url)
    property alias model: gridview.model

    GridView {
        id: gridview
        anchors.fill    : parent
        anchors.margins : units.gu(1)
        cellWidth       : units.gu(13)
        cellHeight      : units.gu(13)
        delegate        : UbuntuShape {
            width       : gridview.cellWidth  - units.gu(1)
            height      : gridview.cellHeight - units.gu(1)
            radius      : "medium"
            color       : model.color || My.randomColor()
            MouseArea {
                anchors.fill: parent
                onClicked: if(model.url) comicSelected(model.url)
            }
        }
    }
}
