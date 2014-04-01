#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include <QFileSystemWatcher>

#include "refresh.h"
#include "c4_window.h"
#include "c4_qml_updater.h"
#include "system_globals.h"
#include "image_ingest_processor.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    C4Window desktop, iPhone, iMini, iPad;
    C4QmlUpdater updater;
    SystemGlobals systemGlobals;
    ImageIngestProcessor imageIngestProcessor;
    imageIngestProcessor.setProxyPath(systemGlobals.dataPath()+"/proxies");

    desktop.addProperty("updater", &updater);
    desktop.addProperty("systemGlobals", &systemGlobals);
    desktop.addProperty("imageIngestProcessor", &imageIngestProcessor);
    desktop.setSource("/x/d/c4/clientC4/src/qml/desktopDesigner.qml");
    desktop.addWatchPath("/x/d/c4/clientC4/src/qml/ViewDesigner.qml");
    desktop.show();

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

    return app.exec();
}
