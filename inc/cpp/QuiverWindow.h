#ifndef QKWINDOW_H
#define QKWINDOW_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFileSystemWatcher>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QDebug>

class QuiverWindow : public QObject
{
  Q_OBJECT
Q_PROPERTY(bool pendingConnectionRequest READ pendingConnectionRequest NOTIFY pendingConnectionRequestChanged)

  QString                 _sourcePath;
  QString _platformName;
  QStringList             *_watchList;
  QQmlApplicationEngine              *_engine;
  QFileSystemWatcher      *_watcher;

  public:
    explicit QuiverWindow(QString sourcePath = QString(), QObject *parent = 0);
    virtual ~QuiverWindow();

    void setSource(const QString & path);
    void setPlatform(const QString & platformName);
    void addWatchPath(const QString & path);
    void addWatchPaths(const QStringList & paths);
    void addProperty(const QString& name, QObject *);

    bool pendingConnectionRequest() const { return m_pending_connectionRequest; }

  public slots:
    void fileChanged(const QString& path);

  signals:
    void pendingConnectionRequestChanged();

private:
    bool m_pending_connectionRequest;
    void detectPlatform();
};

#endif // QKWINDOW_H