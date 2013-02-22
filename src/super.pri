defineReplace(abspath) {
    return($$system(readlink -f $$1))
}

BUILD = $$abspath( $$PWD/../build/ )
SRC   = $$abspath( $$PWD/ )

