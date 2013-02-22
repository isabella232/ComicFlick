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
    comic.load(img);
    repaintComic();
}

void method drawFrameBoundaries(QPainter& p, const QList<comicflick::ComicFrame*>& frames) const {
    QList<QRect> rects;
    for (ComicFrame* f : frames) {
        rects.append(f->rect());
    }
    p.drawRects(rects.toVector());
}

void method repaintComic() {
    QImage img(comic.image);
    QPainter p(&img);
    QColor border = QColor::fromHsl(128, 255, 128, 128);
    QColor filling(border);
    filling.setAlpha(32);
    QPen pen;
    pen.setWidth(3);
    pen.setColor(border);
    p.setPen(pen);
    drawFrameBoundaries(p, comic.frames);
    p.fillRect(comic.current().rect(), filling);
    ui->comicStrip->setPixmap(QPixmap::fromImage(img));
}

void method on_actionRight_triggered() {
    comic.right();
    repaintComic();
}

void MainWindow::on_actionLeft_triggered() {
    comic.left();
    repaintComic();
}

void MainWindow::on_actionUp_triggered() {
    comic.up();
    repaintComic();
}

void MainWindow::on_actionDown_triggered() {
    comic.down();
    repaintComic();
}
