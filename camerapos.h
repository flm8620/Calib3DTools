#ifndef CAMERAPOSITION_H
#define CAMERAPOSITION_H

#include <QtCore>
#include <QVector3D>
#include <vector>
/**
 * @brief CameraPosValue
 * List of pair of matrix R and position C
 */
struct CameraPosValue{
    QList<QPair<std::vector<double>,std::vector<double> > > data;
    bool isValid() const;
};


class CameraPos :public QObject{
    Q_OBJECT
public:
    CameraPos(QObject *parent =0);
    bool isEmpty() const;
    int size() const;
    void clear();
    CameraPosValue getValue() const;
    bool setValue(const CameraPosValue &value);
    double RMatrixElement(int index,int i,int j) const;
    double centerVector(int index,int i) const;
    void setRMatrixElement(int index,int i,int j,double val);
    void setCenterVector(int index,int i,double val);
signals:
    void dataChanged();

protected:
    mutable QReadWriteLock rwLock;

private:
    CameraPosValue value;
};

#endif // CAMERAPOSITION_H
