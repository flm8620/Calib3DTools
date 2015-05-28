#include "point2dview.h"
#include <QDebug>
Point2DView::Point2DView(QWidget *parent)
    :QTreeView(parent)
{
    setHeaderHidden(false);
}


