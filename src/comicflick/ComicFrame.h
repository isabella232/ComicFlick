#pragma once

#include <QtGui>
#include <Qt>
#include <QtCore>

namespace comicflick {

class ComicFrame : public QObject {
    Q_OBJECT
    Q_PROPERTY(QRect my_rect READ rect)
public:
    explicit ComicFrame(QObject *parent = 0);

    ComicFrame(const QRect& rect) : my_rect(rect) {}
    const ComicFrame& left() const;
    const ComicFrame& right() const;
    const ComicFrame& above() const;
    const ComicFrame& below() const;
    const ComicFrame& leftmost() const;
    const ComicFrame& rightmost() const;
    const QRect& rect() const { return my_rect; }
    bool operator < (const ComicFrame& o) const;

    struct Sort {
        Sort(const ComicFrame* f) : f(f) {}
        const ComicFrame* f;
        bool operator < (const Sort& o) const { return *f < *o.f; }
    };
    const Sort sorter() const { return Sort(this); }

    QList<ComicFrame*> frames_left;
    QList<ComicFrame*> frames_right;
    QList<ComicFrame*> frames_above;
    QList<ComicFrame*> frames_below;
private:
    const QRect my_rect;

signals:

public slots:

};

class Comic : public QObject {
    Q_OBJECT
public:
    Comic();
    Comic(const QImage& comic_image);
    ~Comic();
    Q_INVOKABLE void              load          (const QImage& comic_image);
    Q_INVOKABLE const ComicFrame& first         () const;
    Q_INVOKABLE const ComicFrame& current       () const;
    Q_INVOKABLE const ComicFrame& left          ();
    Q_INVOKABLE const ComicFrame& right         ();
    Q_INVOKABLE const ComicFrame& up            ();
    Q_INVOKABLE const ComicFrame& down          ();
    Q_INVOKABLE QImage            currentImage  () const;
    Q_INVOKABLE const ComicFrame* currentFrame  () const { return current_frame; }
    Q_INVOKABLE QVariant          currentRect   () const { return current_frame->rect(); }

    QImage image;
    QList<ComicFrame*> frames;
    const ComicFrame* current_frame;
};

}
