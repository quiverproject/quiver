#include <QuiverWindow.h>
#include <QDebug>

QuiverWindow::QuiverWindow(QObject *parent) : QObject(parent)
{
  _engine = new QQmlApplicationEngine;
//  _window->setResizeMode(QQuickView::SizeRootObjectToView);
//  _window->setWidth(1280);
//  _window->setHeight(752);

//  _window->setFlags(
//                    _window->flags() |
//                    Qt::WindowFullscreenButtonHint
//                    );
  _watcher = new QFileSystemWatcher;

  connect(_watcher,     SIGNAL(fileChanged(const QString&)),
          &_refresher,    SLOT(fileChanged(const QString&)));

  connect(&_refresher, SIGNAL(update()),
          this, SIGNAL(pendingConnectionRequestChanged()));
}

QuiverWindow::~QuiverWindow()
{
  delete _engine;
  delete _watcher;
}

void QuiverWindow::setSource(const QString & path)
{
  _source = path;

  //_window->setSource( QUrl::fromLocalFile(_source) );

  _engine->load(QUrl::fromLocalFile(_source));

  _refresher.setSource(path);
  //_refresher.setEngine(_window->engine());
  _refresher.setEngine(_engine);
  _refresher.setWatcher(_watcher);

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

//void QuiverWindow::show()
//{
//  //_window->show();
//  //_window->showFullScreen();
//}

void QuiverWindow::addProperty(const QString& name, QObject *obj)
{
  _engine->rootContext()->setContextProperty(name, obj);
}

