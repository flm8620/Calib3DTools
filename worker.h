#ifndef WORKER_H
#define WORKER_H

#include <QObject>
class ImageListModel;
class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    explicit Worker(ImageListModel* model,QObject *parent = 0);

signals:

public slots:
    void solve();
private:
    ImageListModel* model;
};

#endif // WORKER_H
