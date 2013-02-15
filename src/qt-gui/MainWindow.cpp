#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QtGui>
#include <QFileDialog>
#include <QImage>

#define method MainWindow::

method MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionExit, &QAction::triggered,
            this, &MainWindow::close);
    connect(ui->actionOpen, &QAction::triggered, [=](bool&) {
        openAndProcessComic(ui->actionOpen->text());
    });
    processComic("why_are_you_reading_this.png");
}

method ~MainWindow()
{
    delete ui;
}

void method openAndProcessComic(const QString &caption) {
    qDebug() << "openAndProcessComic";
    auto paths = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QString filename = QFileDialog::getOpenFileName(this, caption, paths.value(0));
    if (!filename.isNull()) {
        processComic(filename);
    }
}

void method processComic(const QString &filename) {
    qDebug() << "processComic";
    if (!QFile(filename).exists())
        return;
    QImage img(filename);
    img = img.convertToFormat(QImage::Format_ARGB32);
    img = comicflick::paddedImage(img, 2);
    QList<comicflick::Frame*> frames = comicflick::findFrames(img);
    QPainter p(&img);
    p.setPen(Qt::red);
    drawFrameBoundaries(p, frames);
    ui->comicStrip->setPixmap(QPixmap::fromImage(img));
}

void method drawFrameBoundaries(QPainter& p, const QList<comicflick::Frame*>& frames) const {
    QList<QRect> rects;
    for (comicflick::Frame* f : frames) {
        rects.append(f->rect);
    }
    p.drawRects(rects.toVector());
}
