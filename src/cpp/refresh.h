#ifndef REFRESH_H
#define REFRESH_H

#include <QObject>
#include <QString
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQuickView>
#include <QQmlComponent>
#include <QQmlContext>

#include <QFileSystemWatcher>

class Refresher : public QObject
{
    Q_OBJECT

    // QQmlApplicationEngine *_engine;
    QQmlEngine          *_engine;
    QQuickView          *_view;
    QFileSystemWatcher  *_watcher;
    QObject             *_object;
    QQmlContext         *_context;
    QString             *_source;

public:
    explicit Refresher(QObject *parent = 0);
    explicit Refresher(const QString& source, QObject *parent = 0);

    void    setView(QQuickView * view);
    void  setSource(const QString& source);
    void  setEngine(QQmlEngine * engine);
    void setWatcher(QFileSystemWatcher *_watcher);

public slots:

    void fileChanged(const QString& path);

signals:

    void update();
};

#endif // REFRESH_H
