#ifndef MYTEST_H
#define MYTEST_H

#include <QObject>
#include <QAbstractScrollArea>
class MyTest:public QAbstractScrollArea
{
public:
    MyTest(QWidget * parent = 0);
protected:

private:
    void updateViewport();
    void updateWidgetGeo();
    QFrame *frame;
};

#endif // MYTEST_H
