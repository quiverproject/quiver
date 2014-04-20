#ifndef QKWINDOW_H
#define QKWINDOW_H

#include <QQmlEngine>
#include <QQuickView>
#include <QFileSystemWatcher>
#include <QString>
#include <QStringList>

#include <QkRefresher.h>

class QkWindow : public QObject
{
  Q_OBJECT

  QString                 _source;
  QStringList             *_watchList;
  QQuickView              *_window;
  QFileSystemWatcher      *_watcher;

  QkRefresher               _refresher;

  public:
    explicit QkWindow(QObject *parent = 0);
    virtual ~QkWindow();

    void setSource(const QString & path);
    void addWatchPath(const QString & path);
    void addWatchPaths(const QStringList & paths);
    void show();
    void addProperty(const QString& name, QObject *);

  public slots:

  signals:

};

#endif // QKWINDOW_H
