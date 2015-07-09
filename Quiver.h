#ifndef QUIVER_H
#define QUIVER_H

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFileSystemWatcher>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QProcessEnvironment>
#include <QQmlFileSelector>
#include <QQmlImageProviderBase>

class Quiver : public QObject
{
        Q_OBJECT
        Q_PROPERTY(bool pendingConnectionRequest READ pendingConnectionRequest NOTIFY pendingConnectionRequestChanged)
        Q_PROPERTY(bool deploy READ deploy WRITE setDeploy NOTIFY deployChanged)
        QString _sourcePath;
        QString _platformName;
        QStringList *_watchList;
        QQmlApplicationEngine *_engine;
        QFileSystemWatcher *_watcher;
public:
        explicit Quiver(QString sourcePath = QString(), QObject *parent = 0);
        virtual ~Quiver();
        void setSource(const QString &path);
        void setPlatform(const QString &platformName);
        void setDeploy(const bool &deploy) { _deploy = deploy; emit deployChanged(); }
        void addWatchPath(const QString &path);
        void addWatchPaths(const QStringList &paths);
        void addProperty(const QString &name, QObject *);
        void addImageProvider(const QString &name, QQmlImageProviderBase *image_provider);
        bool pendingConnectionRequest() const { return m_pending_connectionRequest; }
        bool deploy() { return _deploy; }
public slots:
        void fileChanged(const QString &path);
signals:
        void pendingConnectionRequestChanged();
        void deployChanged();
private:
        bool m_pending_connectionRequest;
        void detectPlatform();
        void detectDeploy();
        bool _deploy;
};

#endif // QUIVER_H
