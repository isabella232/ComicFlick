#include "ComicFrame.h"

namespace comicflick {

ComicFrame::ComicFrame(QObject *parent) :
    QObject(parent)
{
}

void Comic::setCurrentFrame(const ComicFrame *cf) {
    current_frame = cf;
    changed();
}

};
