#include <QDebug>
#include <QuiverRefresher.h>

#include <iostream>

QuiverRefresher::QuiverRefresher(QObject *parent)
    : QObject(parent)
{
  _object = NULL;
}

QuiverRefresher::QuiverRefresher(const QString& source, QObject *parent)
    : QObject(parent)
{
  _source = source;
}

void QuiverRefresher::fileChanged(const QString& path)
{
  if(_object != NULL)
    delete _object;

  _engine->clearComponentCache();

//   QQmlComponent component(_engine, QUrl::fromLocalFile(path));
//   _object = component.create();

  emit update();
  _watcher->addPath(path);
}

void QuiverRefresher::setSource(const QString& source)
{
  _source = source;
}

void QuiverRefresher::setEngine(QQmlApplicationEngine *engine)
{
  _engine = engine;
}

void QuiverRefresher::setWatcher(QFileSystemWatcher *watcher)
{
  _watcher = watcher;
}

