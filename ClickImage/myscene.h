#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QWidget>
#include <QList>
class QGraphicsSceneWheelEvent;
class QAbstractItemModel;
class myScene: public QGraphicsScene
{
    Q_OBJECT

public:
    enum Mode { InsertItem, MoveItem };
    myScene(QObject *parent = 0);
    void setMode(Mode mode);
signals:
    void requestItemInsert(double x,double y);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    Mode myMode;
};

#endif // MYSCENE_H
