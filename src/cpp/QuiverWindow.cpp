#include <QuiverWindow.h>

QuiverWindow::QuiverWindow(QString sourcePath, QObject *parent) : QObject(parent)
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

QuiverWindow::~QuiverWindow()
{
  delete _engine;
  delete _watcher;
}

void QuiverWindow::detectPlatform() {
  //FIXME try to get a platform name out of an environment variable - otherwise, detect it using qt
  setPlatform("osx");
}

void QuiverWindow::setPlatform(const QString & platformName) {
  _platformName = platformName;
}

void QuiverWindow::setSource(const QString & path)
{
  _sourcePath = path;

  if (_platformName.isEmpty()) {
          detectPlatform();
  }

  QDir platformDir(_sourcePath + "/" + _platformName);
  _engine->load(QUrl::fromLocalFile(platformDir.absolutePath() + "/main.qml"));
  addWatchPath(platformDir.absolutePath());
}

void QuiverWindow::fileChanged(const QString & path)
{
  _engine->clearComponentCache();
  emit pendingConnectionRequestChanged();

  _watcher->addPath(path);
}

void QuiverWindow::addWatchPath(const QString & path)
{
  _watcher->addPath(path);
}

void QuiverWindow::addWatchPaths(const QStringList & paths)
{
  _watcher->addPaths(paths);
}

void QuiverWindow::addProperty(const QString & name, QObject * obj)
{
  _engine->rootContext()->setContextProperty(name, obj);
}
