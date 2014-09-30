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

class QuiverRefresher : public QObject
{
    Q_OBJECT

    QQmlApplicationEngine            *_engine;
    QFileSystemWatcher    *_watcher;
    QString               _source;
    QObject               *_object;

public:
    explicit QuiverRefresher(QObject *parent = 0);
    explicit QuiverRefresher(const QString& source, QObject *parent = 0);

    void    setEngine(QQmlApplicationEngine * engine);
    void  setSource(const QString& source);
    void setWatcher(QFileSystemWatcher *_watcher);

public slots:
    void fileChanged(const QString& path);

signals:
    void update();
};

#endif // QKREFRESHER_H
