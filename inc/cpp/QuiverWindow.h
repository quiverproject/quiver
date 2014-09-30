#ifndef QKWINDOW_H
#define QKWINDOW_H

#include <QQmlEngine>
#include <QQuickView>
#include <QFileSystemWatcher>
#include <QString>
#include <QStringList>

#include <QuiverRefresher.h>

class QuiverWindow : public QObject
{
  Q_OBJECT
Q_PROPERTY(bool pendingConnectionRequest READ pendingConnectionRequest NOTIFY pendingConnectionRequestChanged)

  QString                 _source;
  QStringList             *_watchList;
  QQmlApplicationEngine              *_engine;
  QFileSystemWatcher      *_watcher;

  QuiverRefresher               _refresher;

  public:
    explicit QuiverWindow(QObject *parent = 0);
    virtual ~QuiverWindow();

    void setSource(const QString & path);
    void addWatchPath(const QString & path);
    void addWatchPaths(const QStringList & paths);
//    void show();
    void addProperty(const QString& name, QObject *);

    bool pendingConnectionRequest() const { return m_pending_connectionRequest; }
  public slots:

  signals:
    void pendingConnectionRequestChanged();

private:
    bool m_pending_connectionRequest;
};

#endif // QKWINDOW_H
