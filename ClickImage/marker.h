#ifndef MARKER_H
#define MARKER_H
#include <QGraphicsObject>
class Marker: public QGraphicsObject
{
    Q_OBJECT
public:
    Marker();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*) Q_DECL_OVERRIDE;
private:
    double radius;
    double innerRadius;
};

#endif // MARKER_H
