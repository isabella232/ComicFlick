#pragma once
#include <opencv2/imgproc/imgproc.hpp>
#include <QtGui>

using namespace cv;

namespace comicflick {

struct ComicFrame {
    ComicFrame(const QRect& rect) : rect(rect) {}
    const ComicFrame& left() const;
    const ComicFrame& right() const;
    const ComicFrame& above() const;
    const ComicFrame& below() const;
    const ComicFrame& leftmost() const;
    const ComicFrame& rightmost() const;
    bool operator < (const ComicFrame& o) const;

    struct Sort {
        Sort(const ComicFrame* f) : f(f) {}
        const ComicFrame* f;
        bool operator < (const Sort& o) const { return *f < *o.f; }
    };
    const Sort sorter() const { return Sort(this); }

    const QRect rect;
    QList<ComicFrame*> frames_left;
    QList<ComicFrame*> frames_right;
    QList<ComicFrame*> frames_above;
    QList<ComicFrame*> frames_below;
};

class Comic {
public:
    Comic();
    Comic(const QImage& comic_image);
    ~Comic();
    void              load          (const QImage& comic_image);
    const ComicFrame& first         () const;
    const ComicFrame& current       () const;
    const ComicFrame& left          ();
    const ComicFrame& right         ();
    const ComicFrame& up            ();
    const ComicFrame& down          ();
    QImage            current_image () const;

    QImage image;
    QList<ComicFrame*> frames;
    const ComicFrame* current_frame;
};

vector<vector<Point> > findRectangles(const Mat& image);
QList<QRect> findRectangles(const QImage& image);
QList<ComicFrame*> findFrames(const QImage& image);
QImage paddedImage(const QImage& image, uint padding);

}
