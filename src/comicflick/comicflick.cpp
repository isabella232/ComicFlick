#include "comicflick.h"
#include <QDebug>
#include <opencv2/highgui/highgui.hpp>
#include "ForIterator.h"

namespace comicflick {

// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

// returns sequence of squares detected on the image.
vector<vector<Point> > findRectangles(const Mat& image)
{
    if (image.cols < 2 || image.rows < 2) {
        throw new Exception;
    }
    vector<vector<Point> > rects;
    const int thresh = 50, N = 11;

    Mat pyr, timg, gray0(image.size(), CV_8U), gray;

    // down-scale and upscale the image to filter out the noise
    pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
    pyrUp(pyr, timg, image.size());
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        for( int l = 0; l < N; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 0, thresh, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/N;
            }

            // find contours and store them all as a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            vector<Point> approx;

            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if( approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx)) )
                {
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 )
                        rects.push_back(approx);
                }
            }
        }
    }
    return rects;
}

QList<QRect> findRectangles(const QImage& image) {
    qDebug() << "findRectangles";
    QImage img = image.convertToFormat(QImage::Format_ARGB32);
    Mat mat(img.height(), img.width(), CV_8UC4, img.bits());
    QList<QRect> rects;
    for (vector<Point> v : findRectangles(mat)) {
        int top = INT_MAX, left = INT_MAX, right = INT_MIN, bottom = INT_MIN;
        for (Point p : v) {
            top = min(top, p.y);
            left = min(left, p.x);
            right = max(right, p.x);
            bottom = max(bottom, p.y);
        }
        rects.append(QRect(left, top, right-left, bottom-top));
    }
    return rects;
}

bool containsAll(const QRect& a, const QList<QRect>& rects) {
    for (QRect b : rects) {
        if (a == b) continue;
        if (!a.contains(b))
            return false;
    }
    return true;
}

bool isContained(const QRect& a, const QList<QRect>& rects) {
    for (QRect b : rects) {
        if (a == b) continue;
        if (b.contains(a))
            return true;
    }
    return false;
}

void removeUnlikelyRects(const QImage& image, QList<QRect> &rects) {
    qDebug() << "removeUnlikelyRects;";
    if (rects.empty())
        return;
    int n_rects;
    do {
        n_rects = rects.size();
        for (auto i : ForIterator(rects)) {
            QRect rect = *i;
            if (rect == image.rect() || containsAll(rect, rects)) {
                rects.erase(i);
            }
        }
    } while (n_rects != rects.size());
    for (auto i : ForIterator(rects)) {
        QRect rect = *i;
        if (isContained(rect, rects)) {
            rects.erase(i);
        }
    }
}

QImage paddedImage(const QImage& image, uint padding) {
    QImage img(image.width()+2*padding, image.height()+2*padding, image.format());
    img.fill(Qt::white);
    QPainter p(&img);
    p.drawImage(padding, padding, image);
    return img;
}

bool isAbove(const QRect& a, const QRect& b) {
    return a.bottom() <= b.top();
}

bool isLeft(const QRect& a, const QRect& b) {
    return a.right() <= b.left();
}

bool isRight(const QRect& a, const QRect& b) {
    return a.left() >= b.right();
}

bool isBelow(const QRect& a, const QRect& b) {
    return a.top() >= b.bottom();
}

QList<ComicFrame*> findFrames(const QImage& image) {
    qDebug() << "findFrames";
    QList<QRect> rects = findRectangles(image);
    removeUnlikelyRects(image, rects);
    QMap<ComicFrame::Sort, ComicFrame*> frames;
    for (QRect rect : rects) {
        ComicFrame *frame = new ComicFrame(rect);
        frames.insert(frame->sorter(), frame);
    }
    // look for rects, intersecting with hori./vert. lines
    // sort in axis
    for (ComicFrame* a : frames.values()) {
        QMap<ComicFrame::Sort, ComicFrame*> left, right, above, below;
        for (ComicFrame* b : frames.values()) {
            if (a == b) continue;
            bool    is_left  = isLeft (b->rect, a->rect),
                    is_right = isRight(b->rect, a->rect),
                    is_above = isAbove(b->rect, a->rect),
                    is_below = isBelow(b->rect, a->rect);
            if (is_left  && !is_above && !is_below)
                left.insert(b->sorter(), b);
            if (is_right && !is_above && !is_below)
                right.insert(b->sorter(), b);
            if (is_above && !is_left  && !is_right)
                above.insert(b->sorter(), b);
            if (is_below && !is_left  && !is_right)
                below.insert(b->sorter(), b);
        }
        a->frames_left.append(left.values());
        a->frames_right.append(right.values());
        a->frames_above.append(above.values());
        a->frames_below.append(below.values());
    }
    return frames.values();
}

const ComicFrame& ComicFrame::left() const {
    if (frames_left.empty())
        return *this;
    return *frames_left.last();
}

const ComicFrame& ComicFrame::right() const {
    if (frames_right.empty())
        return *this;
    return *frames_right.first();
}

const ComicFrame& ComicFrame::above() const {
    if (frames_above.empty())
        return *this;
    return *frames_above.last();
}

const ComicFrame& ComicFrame::below() const {
    if (frames_below.empty())
        return *this;
    return *frames_below.first();
}

const ComicFrame& ComicFrame::leftmost() const {
    if (frames_left.empty())
        return *this;
    return *frames_left.first();
}

const ComicFrame& ComicFrame::rightmost() const {
    if (frames_right.empty())
        return *this;
    return *frames_right.last();
}

bool ComicFrame::operator < (const ComicFrame& o) const {
    return isLeft(rect, o.rect) || (rect.bottom() <= o.rect.top());
}

Comic::Comic() {
    frames.append(new ComicFrame(QRect()));
    current_frame = frames.first();
}

Comic::~Comic() {
    for (auto frame : frames) {
        delete frame;
    }
}

Comic::Comic(const QImage &comic_image) {
    load(comic_image);
}

void Comic::load(const QImage& comic_image) {
    for (auto frame : frames) {
        delete frame;
    }
    frames.clear();
    image = comic_image.convertToFormat(QImage::Format_ARGB32);
    image = paddedImage(image, 2);
    frames.append(findFrames(image));
    if (frames.empty()) {
        frames.append(new ComicFrame(image.rect()));
    }
    current_frame = frames.first();
}

const ComicFrame& Comic::first() const {
    return *frames.first();
}

const ComicFrame& Comic::current() const {
    return *current_frame;
}

const ComicFrame& Comic::up() {
    current_frame = &current().above();
    return *current_frame;
}


const ComicFrame& Comic::left() {
    auto left = &current().left();
    auto above = &current().above();
    current_frame =
        left != current_frame ? left :
        above != current_frame ? &above->rightmost() :
        current_frame;
    return *current_frame;
}

const ComicFrame& Comic::right() {
    auto right = &current().right();
    auto below = &current().below();
    current_frame =
        right != current_frame ? right :
        below != current_frame ? &below->leftmost() :
        current_frame;
    return *current_frame;
}

const ComicFrame& Comic::down() {
    current_frame = &current().below();
    return *current_frame;
}

}
