#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>
#include <QFileDialog>
#include "comicflick.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openAndProcessComic(const QString &caption);
    void processComic(const QString &filename);
    void drawFrameBoundaries(QPainter& p, const QList<comicflick::Frame*>& frames) const;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
