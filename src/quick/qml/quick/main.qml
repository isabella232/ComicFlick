import QtQuick 2.0

Rectangle {
    id: root
    width: 360
    height: 360
    focus: true
    Image {
        id: comicImage
        source: "file:./../../why_are_you_reading_this.png"
    }
    Keys.onPressed: {
        var action_keys_map = {
            "comic.up"   : [ Qt.Key_Up   , Qt.Key_W, Qt.Key_J ],
            "comic.down" : [ Qt.Key_Down , Qt.Key_S, Qt.Key_K ],
            "comic.left" : [ Qt.Key_Left , Qt.Key_A, Qt.Key_H ],
            "comic.right": [ Qt.Key_Right, Qt.Key_D, Qt.Key_L ]
        }
        var action_fun_map = {
            "comic.up"   : function() { comic.up() },
            "comic.down" : function() { comic.down() },
            "comic.left" : function() { comic.left() },
            "comic.right": function() { comic.right() }
        }
        for (var action in action_keys_map) {
            var keys = action_keys_map[action];
            var fun  = action_fun_map [action];
            if (keys.indexOf(event.key) !== -1) {
                fun();
                var rect = comic.currentRect()
                comicImage.x = -rect.x
                comicImage.y = -rect.y
            }
        }
    }
}
