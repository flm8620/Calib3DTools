#ifndef POINT3DWIDGET_H
#define POINT3DWIDGET_H

#include <QWidget>
class Point3DModel;
class QTableView;
class Point3DWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Point3DWidget(QWidget *parent = 0);
    void setModel(Point3DModel* model);

public slots:
    void appendPoint();
    void removePoint();
    void moveUp();
    void moveDown();

private:
    QModelIndex getFirstSelectedItem();
    Point3DModel* model;
    QTableView* view;
};

#endif // POINT3DWIDGET_H
