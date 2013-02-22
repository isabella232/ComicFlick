defineReplace(abspath) {
    return($$system(readlink -f $$1))
}

BUILD = $$abspath( $$PWD/../build/ )
CONFIG(debug, debug|release): BUILD = $$BUILD/debug/
CONFIG(release, debug|release): BUILD = $$BUILD/release/

SRC   = $$abspath( $$PWD/ )

CONFIG(release, debug|release):: DEFINES += QT_NO_DEBUG_OUTPUT
