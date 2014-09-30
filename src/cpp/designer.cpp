#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include <QFileSystemWatcher>
#include <QDir>

#include <Qkit.h>
#include <QkRefresher.h>
#include <QkWindow.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QuiverWindow desktop;
    // running from: .build/designer/Qkit.app/Contents/MacOS/Qkit
    desktop.setSource(QDir::currentPath() + "/src/qml/desktopPlatform.qml");
    desktop.addWatchPath(QDir::currentPath() + "/src/qml/Main.qml");
    desktop.show();
    return app.exec();
}

/*
    // We'll come back to this:

    // This should probably be automatically handled by configuration
    // And maybe a QkPlatform class that reads the config and builds
    // the interfaces / deployments automatically.

    iPad.addProperty("updater", &updater);
    iPad.addProperty("systemGlobals", &systemGlobals);
    iPad.addProperty("imageIngestProcessor", &imageIngestProcessor);
    iPad.setSource("/x/d/c4/clientC4/src/qml/iPadDesigner.qml");
    iPad.addWatchPath("/x/d/c4/clientC4/src/qml/ViewDesigner.qml");
    iPad.show();

    iPhone.setSource("/x/d/c4/clientC4/src/qml/iPhoneDesigner.qml");
    iPhone.addWatchPath("/x/d/c4/clientC4/src/qml/ViewDesigner.qml");

    iMini.setSource("/x/d/c4/clientC4/src/qml/iMiniDesigner.qml");
    iMini.addWatchPath("/x/d/c4/clientC4/src/qml/ViewDesigner.qml");

    iPhone.show();
    iMini .show();
*/


