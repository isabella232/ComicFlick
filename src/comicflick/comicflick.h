#pragma once
#include <opencv2/imgproc/imgproc.hpp>
#include <QtGui>
#include "ComicFrame.h"

using namespace cv;

namespace comicflick {

vector<vector<Point> > findRectangles(const Mat& image);
QList<QRect> findRectangles(const QImage& image);
QList<ComicFrame*> findFrames(const QImage& image);
QImage paddedImage(const QImage& image, uint padding);

}
