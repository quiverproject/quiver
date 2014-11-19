#include <Quiver.h>

Quiver::Quiver(QString sourcePath, QObject *parent) : QObject(parent)
{
  _engine = new QQmlApplicationEngine;
  addProperty("quiver", this);

  _watcher = new QFileSystemWatcher;
  connect(_watcher,     SIGNAL(fileChanged(const QString&)),
    this,    SLOT(fileChanged(const QString&)));
  connect(_watcher,     SIGNAL(directoryChanged(const QString&)),
    this,    SLOT(fileChanged(const QString&)));

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


        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        if (env.contains("Quiver_platformName") && !env.value("Quiver_platformName").isEmpty()) {
                platform_name = env.value("Quiver_platformName");
        }


        setPlatform(platform_name);
}

void Quiver::setPlatform(const QString & platformName) {
  _platformName = platformName;
}

void Quiver::setSource(const QString & path)
{
  _sourcePath = path;

  if (_platformName.isEmpty()) {
          detectPlatform();
  }

  QDir platformDir(_sourcePath + "/" + _platformName);
  _engine->addImportPath(_sourcePath);
  _engine->load(QUrl::fromLocalFile(platformDir.absolutePath() + "/main.qml"));
  addWatchPath(platformDir.absolutePath());
}

void Quiver::fileChanged(const QString & path)
{
  _engine->clearComponentCache();
  emit pendingConnectionRequestChanged();

  _watcher->addPath(path);
}

void Quiver::addWatchPath(const QString & path)
{
  _watcher->addPath(path);
}

void Quiver::addWatchPaths(const QStringList & paths)
{
  _watcher->addPaths(paths);
}

void Quiver::addProperty(const QString & name, QObject * obj)
{
  _engine->rootContext()->setContextProperty(name, obj);
}
