#include <QProcessEnvironment>
#include <Quiver.h>

Quiver::Quiver(QString sourcePath, QObject *parent) : QObject(parent)
{
        _engine = new QQmlApplicationEngine;
        new QQmlFileSelector(_engine);
        addProperty("quiver", this);

        _watcher = new QFileSystemWatcher;
        connect(_watcher,     SIGNAL(fileChanged(const QString&)),
                this,    SLOT(fileChanged(const QString&)));
        connect(_watcher,     SIGNAL(directoryChanged(const QString&)),
                this,    SLOT(fileChanged(const QString&)));

        detectDeploy();

        if (!sourcePath.isEmpty()) {
                setSource(sourcePath);
        }
}

Quiver::~Quiver()
{
        delete _engine;
        delete _watcher;
}

void Quiver::detectPlatform() {
        QString platform_name("unknown");


#ifdef Q_OS_IOS
        platform_name = "ios";
#endif

#ifdef Q_OS_MACX
        platform_name = "osx";
#endif

#ifdef Q_OS_WIN
        platform_name = "win";
#endif


#ifndef Q_OS_IOS //this broke in qt 5.5.0 (20150707)
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        if (env.contains("Quiver_platformName") && !env.value("Quiver_platformName").isEmpty()) {
                platform_name = env.value("Quiver_platformName");
        }
#endif


        setPlatform(platform_name);
}

void Quiver::setPlatform(const QString &platformName) {
        _platformName = platformName;
}

void Quiver::detectDeploy() {
        bool deploy = true;

#ifndef Q_OS_IOS //this broke in qt 5.5.0 (20150707)
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        if (env.contains("Quiver_deploy") && !env.value("Quiver_deploy").isEmpty()) {
                deploy = env.value("Quiver_deploy") == "1" ? true : false;
        }
#endif

        setDeploy(deploy);
}

void Quiver::setSource(const QString &path) {
        _sourcePath = path;

        if (_platformName.isEmpty()) {
                detectPlatform();
        }

        if (_deploy) {
                _engine->addImportPath("qrc:/" + _sourcePath);
                _engine->load(QUrl("qrc:/" + _sourcePath + "/" + _platformName + "/main.qml"));
        } else {
                _engine->addImportPath(_sourcePath);
                QDir platformDir(_sourcePath + "/" + _platformName);
                _engine->load(QUrl::fromLocalFile(platformDir.absolutePath() + "/main.qml"));
                addWatchPath(platformDir.absolutePath());
        }

        //switched from stdout to stderr because the message was getting lost under os x 10.8 (20150709)
        fprintf(stderr, "Quiver: main.qml loaded\n"); //this must be printf() and not qDebug() << for some reason ... (20141125)
        fflush(stderr);
}

void Quiver::addImportPath(const QString &path) {
        if (_deploy) {
                _engine->addImportPath("qrc:/" + path);
        } else {
                _engine->addImportPath(path);
                addWatchPath(QDir(path).absolutePath());
        }
}

void Quiver::fileChanged(const QString &path) {
        _engine->clearComponentCache();
        emit pendingConnectionRequestChanged();

        _watcher->addPath(path);
}

void Quiver::addWatchPath(const QString &path) {
        _watcher->addPath(path);
}

void Quiver::addWatchPaths(const QStringList &paths) {
        _watcher->addPaths(paths);
}

void Quiver::addProperty(const QString &name, QObject *obj) {
        _engine->rootContext()->setContextProperty(name, obj);
}

void Quiver::addImageProvider(const QString &name, QQmlImageProviderBase *image_provider) {
        _engine->addImageProvider(name, image_provider);
}
