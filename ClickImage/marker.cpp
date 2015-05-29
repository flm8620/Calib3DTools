#include "marker.h"
#include <QtWidgets>
#include <QDebug>
#include <cstdlib>
Marker::Marker(int id)
{
    setFlags(ItemIsSelectable|ItemIsMovable);
    setAcceptHoverEvents(true);
    setZValue(10);
    radius=24.0;
    innerRadius=15.0;
    this->id=id;
}

QRectF Marker::boundingRect() const
{
    return QRectF(-radius-1,-radius-1,radius*2+3,radius*2+3);

}

QPainterPath Marker::shape() const
{
    QPainterPath path;
    path.addEllipse(-radius,-radius,radius*2+1,radius*2+1);
    return path;
}

void Marker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /*widget*/)
{
    //qDebug()<<"marker paint"<<rand();
    QColor color=Qt::blue;

    if(option->state & QStyle::State_Selected)
        color=Qt::yellow;
    if(option->state & QStyle::State_MouseOver)
        color=color.dark();
    //qDebug()<<option->state;

    QPainterPath circle,triangle;
    circle.addEllipse(-radius,-radius,radius*2+1,radius*2+1);
    circle.addEllipse(-innerRadius,-innerRadius,innerRadius*2+1,innerRadius*2+1);
    circle.setFillRule(Qt::OddEvenFill);

    painter->save();
    painter->setBrush(color);
    painter->setPen(Qt::blue);
    painter->drawPath(circle);
    painter->drawLine(-innerRadius,0,innerRadius,0);
    painter->drawLine(0,-innerRadius,0,innerRadius);
    painter->restore();



}



