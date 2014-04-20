#include <QkWindow.h>
#include <QDebug>

QkWindow::QkWindow(QObject *parent) : QObject(parent)
{
  _window = new QQuickView;
  _window->setResizeMode(QQuickView::SizeRootObjectToView);
  _window->setWidth(1280);
  _window->setHeight(752);

  _window->setFlags(
                    _window->flags() |
                    Qt::WindowFullscreenButtonHint
                    );
  _watcher = new QFileSystemWatcher;
  connect(_watcher,     SIGNAL(fileChanged(const QString&)),
          &_refresher,    SLOT(fileChanged(const QString&)));
  connect (&_refresher, SIGNAL(update()),
            _window,      SLOT(update()));
}

QkWindow::~QkWindow()
{
  delete _window;
  delete _watcher;
}

void QkWindow::setSource(const QString & path)
{
  _source = path;
  _window->setSource( QUrl::fromLocalFile(_source) );
  _refresher.setSource(path);
  _refresher.setEngine(_window->engine());
  _refresher.setView(_window);
  _refresher.setWatcher(_watcher);
  _watcher->addPath(path);
}

void QkWindow::addWatchPath(const QString & path)
{
  _watcher->addPath(path);
}

void QkWindow::addWatchPaths(const QStringList & paths)
{
  _watcher->addPaths(paths);
}

void QkWindow::show()
{
  _window->show();
  //_window->showFullScreen();
}

void QkWindow::addProperty(const QString& name, QObject *obj)
{
  _window->rootContext()->setContextProperty(name, obj);
}

