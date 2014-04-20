#include <QDebug>
#include <QkRefresher.h>

#include <iostream>

QkRefresher::QkRefresher(QObject *parent)
    : QObject(parent)
{
  _object = NULL;
}

QkRefresher::QkRefresher(const QString& source, QObject *parent)
    : QObject(parent)
{
  _object = NULL;
  _source = source;
}

void QkRefresher::fileChanged(const QString& path)
{
  if(_object != NULL)
    delete _object;

  _engine->clearComponentCache();
  _view->setSource(QUrl::fromLocalFile(_source));
  // _engine->load(path);

  // QQmlComponent component(_engine, QUrl::fromLocalFile(path));

  // _object = component.create();
  // _object->setParent(_engine->rootObjects().value(1));

  emit update();
  _watcher->addPath(path);
}

void QkRefresher::setSource(const QString& source)
{
  _source = source;
}

void QkRefresher::setView(QQuickView * view)
{
  _view = view;
}
void QkRefresher::setEngine(QQmlEngine * engine)
{
  _engine = engine;
}

void QkRefresher::setWatcher(QFileSystemWatcher *watcher)
{
  _watcher = watcher;
}

