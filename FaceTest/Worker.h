#ifndef WORKER_H
#define WORKER_H

#include <QImage>
#include <QObject>
#include <QRunnable>

class Worker : public QObject {
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

public slots:
    void doWork(const QImage &image);

signals:
    void resultReady(QByteArray data);
};

#endif // WORKER_H
