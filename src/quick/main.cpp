#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QQuickImageProvider>
#include "comicflick.h"
#include <QtQml>
#include <QQmlDebuggingEnabler>

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
    QQmlDebuggingEnabler qml_debug;
    QGuiApplication app(argc, argv);

    QString filepath = app.arguments().value(1, "./why_are_you_reading_this.png");
    Comic comic;
    if (QFile(filepath).exists()) {
        comic.load(QImage(filepath));
    }

    QtQuick2ApplicationViewer viewer;
    viewer.engine()->addImageProvider("comicimageprovider", new ComicImageProvider(comic));
    QQmlContext* context = viewer.rootContext();
    context->setContextProperty("comic", &comic);
    viewer.setMainQmlFile(QStringLiteral("qml/quick/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
