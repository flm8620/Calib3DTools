#ifndef POINT2DWIDGET_H
#define POINT2DWIDGET_H

#include <QWidget>
class Point2DView;
class Point2DModel;
class Point2DWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Point2DWidget(QWidget *parent = 0);
    void setModel(Point2DModel *model);
    Point2DView *getPoint2DView();
signals:

public slots:
    void addPoint();
    void removePoint();
    void moveUp();
    void moveDown();
private:
    QModelIndex getFirstSelectedItem();
    Point2DModel *model;
    Point2DView *view;
};

#endif // POINT2DWIDGET_H
