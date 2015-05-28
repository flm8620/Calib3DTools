#ifndef POINT2DVIEW_H
#define POINT2DVIEW_H

#include <QObject>
#include <QTreeView>
class Point2DView : public QTreeView
{
    Q_OBJECT
public:
    Point2DView(QWidget* parent=0);

};

#endif // POINT2DVIEW_H
