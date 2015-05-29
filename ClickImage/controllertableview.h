#ifndef CONTROLLERTABLEVIEW_H
#define CONTROLLERTABLEVIEW_H

#include <QObject>
#include <QTableView>
class ControllerTableView:public QTableView
{
    Q_OBJECT
public:
    ControllerTableView(QWidget * parent = 0);
public slots:
    void addOneItem();
    void removeOneItem();
    void moveUp();
    void moveDown();

};

#endif // CONTROLLERTABLEVIEW_H
