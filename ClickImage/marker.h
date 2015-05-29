#ifndef MARKER_H
#define MARKER_H
#include <QGraphicsObject>
class Marker: public QGraphicsObject
{
public:
    Marker(int id);
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*) Q_DECL_OVERRIDE;
private:
    int id;
    double radius;
    double innerRadius;
};

#endif // MARKER_H
