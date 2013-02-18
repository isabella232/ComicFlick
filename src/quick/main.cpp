#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QQuickImageProvider>
#include "comicflick.h"

using namespace comicflick;

struct ComicFrameProvider : QQuickImageProvider {
    ComicFrameProvider(const Comic& comic) :
        QQuickImageProvider(QQuickImageProvider::Image),
        comic(comic) {
    }

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) {
        return comic.current_image();
    }

    const Comic& comic;
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Comic comic;
    if (QFile("why_are_you_reading_this.png").exists()) {
        comic.load(QImage("why_are_you_reading_this.png"));
    }

    QtQuick2ApplicationViewer viewer;
    viewer.engine()->addImageProvider("comicframeprovider", new ComicFrameProvider(comic));
    viewer.setMainQmlFile(QStringLiteral("qml/quick/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
