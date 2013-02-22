#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "comicflick.h"

using namespace comicflick;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openAndProcessComicByDialog();
    void openAndProcessComic(const QString &caption);
    void processComic(const QString &filename);
    void drawFrameBoundaries(QPainter& p, const QList<comicflick::ComicFrame*>& frames) const;
private slots:
    void on_actionRight_triggered();

    void on_actionLeft_triggered();

    void on_actionUp_triggered();

    void on_actionDown_triggered();

private:
    Ui::MainWindow *ui;
    Comic comic;
    void repaintComic();
};

#endif // MAINWINDOW_H
