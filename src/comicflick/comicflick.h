#pragma once
#include <opencv2/imgproc/imgproc.hpp>
#include <QtGui>

using namespace cv;

namespace comicflick {

class Comic;
class ComicFrame;

vector<vector<Point> >      findRectangles          (const Mat& image);
QList<QRect>                findRectangles          (const QImage& image);
QList<ComicFrame*>          findFrames              (const QImage& image);
QImage                      paddedImage             (const QImage& image, uint padding);
bool                        isLeft                  (const QRect& a, const QRect& b);
bool                        isRight                 (const QRect& a, const QRect& b);
bool                        isAbove                 (const QRect& a, const QRect& b);
bool                        isBelow                 (const QRect& a, const QRect& b);



class ComicFrame : public QObject {
    Q_OBJECT
    Q_PROPERTY(QRect my_rect
               READ         rect)
public:
    explicit                ComicFrame              (QObject *parent = 0);
                            ComicFrame              (const QRect& rect) : my_rect(rect) {}
    const ComicFrame&       left                    () const;
    const ComicFrame&       right                   () const;
    const ComicFrame&       above                   () const;
    const ComicFrame&       below                   () const;
    const ComicFrame&       leftmost                () const;
    const ComicFrame&       rightmost               () const;
    const QRect&            rect                    () const { return my_rect; }
    bool                    operator <              (const ComicFrame& o) const;

    struct Sort {
                            Sort                    (const ComicFrame* f) : f(f) {}
        bool                operator <              (const Sort& o) const { return *f < *o.f; }
        const ComicFrame*   f;
    };
    const Sort              sorter                  () const { return Sort(this); }

    QList<ComicFrame*>      frames_left;
    QList<ComicFrame*>      frames_right;
    QList<ComicFrame*>      frames_above;
    QList<ComicFrame*>      frames_below;
private:
    const QRect             my_rect;
};



class Comic : public QObject {
    Q_OBJECT
    Q_PROPERTY(QImage m_image
               READ         image)
    Q_PROPERTY(const ComicFrame* current_frame
               READ         currentFrame
               WRITE        setCurrentFrame
               NOTIFY       changed)
public:
                            Comic                   ();
                            Comic                   (const QImage& comic_image);
                            ~Comic                  ();
    Q_INVOKABLE void                load            (const QImage& comic_image);
    Q_INVOKABLE const ComicFrame&   first           () const;
    Q_INVOKABLE const ComicFrame&   current         () const;
    Q_INVOKABLE const ComicFrame&   left            ();
    Q_INVOKABLE const ComicFrame&   right           ();
    Q_INVOKABLE const ComicFrame&   up              ();
    Q_INVOKABLE const ComicFrame&   down            ();
    Q_INVOKABLE QImage              currentImage    () const;
    Q_INVOKABLE const ComicFrame*   currentFrame    () const { return current_frame; }
    Q_INVOKABLE void                setCurrentFrame (const ComicFrame* cf);
    Q_INVOKABLE QVariant            currentRect     () const { return current_frame->rect(); }
    const QImage&                   image           () const { return m_image; }
    QList<ComicFrame*>              frames;
    const ComicFrame*               current_frame;
signals:
    void                            changed         ();
private:
    QImage                          m_image;
};


}
