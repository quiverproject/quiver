#ifndef QKREFRESHER_H
#define QKREFRESHER_H

#include <QObject>
#include <QString>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQuickView>
#include <QQmlComponent>
#include <QQmlContext>

#include <QFileSystemWatcher>

class QkRefresher : public QObject
{
    Q_OBJECT

    // QQmlApplicationEngine *_engine;
    QQmlEngine          *_engine;
    QQuickView          *_view;
    QFileSystemWatcher  *_watcher;
    QObject             *_object;
    QQmlContext         *_context;
    QString             _source;

public:
    explicit QkRefresher(QObject *parent = 0);
    explicit QkRefresher(const QString& source, QObject *parent = 0);

    void    setView(QQuickView * view);
    void  setSource(const QString& source);
    void  setEngine(QQmlEngine * engine);
    void setWatcher(QFileSystemWatcher *_watcher);

public slots:

    void fileChanged(const QString& path);

signals:

    void update();
};

#endif // QKREFRESHER_H
