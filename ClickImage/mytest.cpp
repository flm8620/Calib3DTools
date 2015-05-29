#include "mytest.h"
#include <QtWidgets>
#include <QDebug>
MyTest::MyTest(QWidget *parent)
    :QAbstractScrollArea(parent)
{
    QMargins margin(20,20,20,20);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    frame=new QFrame(this);
    QWidget* b1= new QPushButton("111",frame);
    QWidget* b2= new QPushButton("222",frame);
    QWidget* b3= new QPushButton("333",frame);
    b1->move(0,0);
    b2->move(50,50);
    b3->move(100,100);
    frame->setFrameShadow(QFrame::Sunken);
    frame->setFrameShape(QFrame::Box);
    frame->setLineWidth(10);
    frame->move(0,0);
    frame->resize(QSize(500,500));
    frame->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    //setViewportMargins(margin);
}



void MyTest::updateViewport()
{
    QSize areaSize=viewport()->size();
    QSize widgetSize=frame->size();
    qDebug()<<"area:"<<areaSize;
    verticalScrollBar()->setPageStep(areaSize.height());
    horizontalScrollBar()->setPageStep(areaSize.width());
    verticalScrollBar()->setRange(0, widgetSize.height() - areaSize.height());
    horizontalScrollBar()->setRange(0, widgetSize.width() - areaSize.width());
    updateWidgetGeo();
}

void MyTest::updateWidgetGeo()
{
    int hvalue = horizontalScrollBar()->value();
    int vvalue = verticalScrollBar()->value();
    QPoint topLeft = viewport()->rect().topLeft();

    frame->move(topLeft.x() - hvalue, topLeft.y() - vvalue);
}

