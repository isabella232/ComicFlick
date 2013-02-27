import QtQuick 2.0
import Ubuntu.Components 0.1
import 'helpers.js' as My

Page {
    signal comicSelected(QtObject model, rect rect)
    property alias model: gridview.model

    GridView {
        id: gridview
        anchors.fill    : parent
        anchors.margins : units.gu(1)
        cellWidth       : units.gu(13)
        cellHeight      : units.gu(13)
        delegate        : ComicsPageItem {
            onPressAndHold: {
                var rect
                rect = parent.mapToItem(null, parent.x, parent.y, parent.width, parent.height)
                rect = Qt.rect(rect.x, rect.y, rect.width, rect.height)
                comicSelected(model, rect)
            }
        }
    }
}
