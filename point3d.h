#ifndef TARGET3D_H
#define TARGET3D_H

#include <QtCore>
#include <QVector3D>

class Point3D : public QObject
{
    Q_OBJECT
public:
    Point3D(QObject *parent = 0);
    bool isEmpty() const
    {
        QReadLocker locker(&this->rwLock);
        return this->_data.size() == 0;
    }

    int pointCount() const
    {
        QReadLocker locker(&this->rwLock);
        return this->_data.size();
    }

    void clear();
    void append();
    void remove(int index);
    void moveUp(int index);
    void moveDown(int index);
    QVector3D getPoint(int index) const;
    void setPoint(int index, QVector3D point);
    void getContent(QList<QVector3D> &out);
    void setContent(QList<QVector3D> &in);
signals:
    void dataChanged();
protected:
    mutable QReadWriteLock rwLock;
private:
    QList<QVector3D> _data;
};

#endif // TARGET3D_H
