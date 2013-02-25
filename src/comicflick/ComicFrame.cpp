#include "comicflick.h"
using namespace comicflick;
#define method ComicFrame::

method ComicFrame(QObject *parent) :
    QObject(parent) {
}

const ComicFrame& method left() const {
    if (frames_left.empty())
        return *this;
    return *frames_left.last();
}

const ComicFrame& method right() const {
    if (frames_right.empty())
        return *this;
    return *frames_right.first();
}

const ComicFrame& method above() const {
    if (frames_above.empty())
        return *this;
    return *frames_above.last();
}

const ComicFrame& method below() const {
    if (frames_below.empty())
        return *this;
    return *frames_below.first();
}

const ComicFrame& method leftmost() const {
    if (frames_left.empty())
        return *this;
    return *frames_left.first();
}

const ComicFrame& method rightmost() const {
    if (frames_right.empty())
        return *this;
    return *frames_right.last();
}

bool method operator < (const ComicFrame& o) const {
    return isLeft(rect(), o.rect()) || (rect().bottom() <= o.rect().top());
}
