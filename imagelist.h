#ifndef IMAGELIST_H
#define IMAGELIST_H

#include <QtCore>
#include <QtGui>
// typedef QList<QImage> ImageList;

class ImageList : public QObject
{
    Q_OBJECT
public:
    ImageList(QObject *parent = 0);
    bool isEmpty() const;
    void clear();
    int size() const;
    void append(const QString &name, const QImage &image);
    void setImage(int index, const QImage &image);
    void setName(int index, const QString &name);
    void remove(int index);
    QImage getImage(int index) const;
    QString getName(int index) const;
    void getContent(QList<QPair<QString, QImage> >& listOut) const;
    void setContent(QList<QPair<QString, QImage> >& listIn);
    void moveUp(int index);
    void moveDown(int index);
signals:
    void dataChanged();
protected:
    mutable QReadWriteLock rwLock;
private:
    bool indexValid(int index) const;
    QList<QPair<QString, QImage> > imageData;
};

#endif // IMAGELIST_H
