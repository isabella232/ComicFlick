#include <QtQuick>
#include "qtquick2applicationviewer.h"
#include "comicflick.h"
#include <QDebug>

using namespace comicflick;

struct ComicImageProvider : QQuickImageProvider {
    ComicImageProvider(const Comic& comic) :
        QQuickImageProvider(QQuickImageProvider::Image),
        comic(comic) {
    }

    QImage requestImage(const QString &/*id*/, QSize */*size*/, const QSize &/*requestedSize*/) {
        return QImage(comic.image());
    }

    const Comic& comic;
};

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QString filepath = app.arguments().value(1, "./why_are_you_reading_this.png");
    filepath = QDir().absoluteFilePath(filepath);
    Comic comic;
    if (QFile(filepath).exists()) {
        comic.load(QImage(filepath));
    } else {
        qDebug() << "File does not exist:" << filepath;
    }

    QtQuick2ApplicationViewer viewer;
    viewer.engine()->addImageProvider("comicimageprovider", new ComicImageProvider(comic));
    QQmlContext* context = viewer.rootContext();
    context->setContextProperty("comic", &comic);
    viewer.setMainQmlFile(QStringLiteral("qml/quick/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
