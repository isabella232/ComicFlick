#include "comicflick.h"
using namespace comicflick;
#define method Comic::

void method setCurrentFrame(const ComicFrame *cf) {
    current_frame = cf;
    changed();
}

method Comic() {
    frames.append(new ComicFrame(QRect()));
    setCurrentFrame(frames.first());
}

method ~Comic() {
    for (auto frame : frames) {
        delete frame;
    }
}

method Comic(const QImage &comic_image) {
    load(comic_image);
}

void method load(const QImage& comic_image) {
    for (auto frame : frames) {
        delete frame;
    }
    frames.clear();
    m_image = comic_image.convertToFormat(QImage::Format_ARGB32);
    m_image = paddedImage(m_image, 2);
    frames.append(findFrames(m_image));
    if (frames.empty()) {
        frames.append(new ComicFrame(m_image.rect()));
    }
    setCurrentFrame(frames.first());
}

const ComicFrame& method first() const {
    return *frames.first();
}

const ComicFrame& method current() const {
    return *current_frame;
}

const ComicFrame& method up() {
    setCurrentFrame(&current().above());
    return *current_frame;
}


const ComicFrame& method left() {
    auto left = &current().left();
    auto above = &current().above();
    setCurrentFrame(
        left != current_frame ? left :
        above != current_frame ? &above->rightmost() :
        current_frame);
    return *current_frame;
}

const ComicFrame& method right() {
    auto right = &current().right();
    auto below = &current().below();
    setCurrentFrame(
        right != current_frame ? right :
        below != current_frame ? &below->leftmost() :
        current_frame);
    return *current_frame;
}

const ComicFrame& method down() {
    setCurrentFrame(&current().below());
    return *current_frame;
}

QImage method currentImage() const {
    return image().copy(current().rect());
}
