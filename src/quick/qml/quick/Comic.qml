import QtQuick 2.0
import Ubuntu.Components 0.1

Flickable {
    id                  : root
    anchors.fill        : parent
    contentWidth        : image.width  * 2
    contentHeight       : image.height * 2

    property bool zoom  : true

    Connections {
        target: comic
        onChanged: comicChanged()
    }

    Component.onCompleted: comicChanged()

    SmoothProperty on contentX {}
    SmoothProperty on contentY {}

    Item {
        visible : false
        id      : imageFrame
        x       : image.x
        y       : image.y
        width   : image.width
        height  : image.height
        transformOrigin: Item.Center
        transform: Scale {
            id: scale
            onXScaleChanged: imageScale.xScale = xScale
            onYScaleChanged: imageScale.yScale = yScale
        }
    }

    Image {
        id      : image
        source  : "image://comicimageprovider/current"
        x       : contentWidth/2  - width/2
        y       : contentHeight/2 - height/2
        transformOrigin: Item.Center
        transform: Scale {
            id: imageScale
            SmoothProperty on xScale {}
            SmoothProperty on yScale {}
        }
        /* DEBUG
        Rectangle {
            id: debug
            color: "#ff0000"
            width: 10
            height: 10
        }
        */
    }

    onFlickStarted: { console.debug("onFlickStarted");
        if (flickingHorizontally && horizontalVelocity > 0)
            comic.right();
        if (flickingHorizontally && horizontalVelocity < 0)
            comic.left();
        if (flickingVertically && verticalVelocity > 0)
            comic.down();
        if (flickingVertically && verticalVelocity < 0)
            comic.up();
    }

    onMovingChanged: {/* TODO
        if (flicking) return; // prevents the first call after a flick, not the second
        if (moving) return;
        console.debug("movementEnded");
        var x = contentX - image.width/2
        var y = contentY
        var p = root.mapToItem(imageFrame, x, y)
        debug.x = p.x
        debug.y = p.y
        console.debug(p.x, p.y)
        comic.setCurrentToNearestFrame(Qt.point(p.x, p.y))*/
    }

    function comicChanged() { console.debug("comicChanged");
        updatePosition()
    }

    function updatePosition() {
        var ratio = getRatio()
        scale.xScale = ratio
        scale.yScale = ratio
        var rect = comic.currentRect()
        var mapped = imageFrame.mapToItem(root, rect.x, rect.y, rect.width, rect.height)
        contentX += mapped.x + mapped.width/2  - root.width/2
        contentY += mapped.y + mapped.height/2 - root.height/2
    }

    function getRatio() {
        var rect      = comic.currentRect();
        var rootRatio =      width /      height;
        var rectRatio = rect.width / rect.height;
        return !zoom ? 1 : rectRatio > rootRatio?
            width  / rect.width :
            height / rect.height;
    }
}
