#pragma once
#include <opencv2/imgproc/imgproc.hpp>
#include <QtGui>

using namespace cv;

namespace comicflick {

struct Frame {
    const QRect rect;
    QList<Frame*> left;
    QList<Frame*> right;
    Frame(const QRect& rect) : rect(rect) {}
};

/*
struct Comic {
    Comic(const QImage& image);
    const Frame& firstFrame();
    const Frame* leftFrame(const Frame& frame);
    const Frame* rightFr
};
*/

vector<vector<Point> > findRectangles(const Mat& image);
QList<QRect> findRectangles(const QImage& image);
QList<Frame*> findFrames(const QImage& image);
QImage paddedImage(const QImage& image, uint padding);

}
