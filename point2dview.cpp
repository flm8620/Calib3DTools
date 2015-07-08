#include "point2dview.h"
#include <QDebug>
Point2DView::Point2DView(QWidget *parent) :
    QTreeView(parent)
{
    this->setHeaderHidden(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);

}

void Point2DView::setPoint2DModel(Point2DModel *point2DModel)
{
    this->point2DModel = point2DModel;
    QTreeView::setModel(point2DModel);
    connect(this->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
            SLOT(onSelectionChanged(QItemSelection)));
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(onCurrentChanged(QModelIndex)));
}

void Point2DView::onSelectionChanged(const QItemSelection &selected)
{
    if (selected.isEmpty()) return;
    QModelIndex current = selected.first().indexes().first();
    this->onCurrentChanged(current);
}

void Point2DView::onCurrentChanged(const QModelIndex &current)
{
    if (this->point2DModel->indexMeansImage(current)) {
        emit currentPointChanged(current.row(), 0);
    } else if (this->point2DModel->indexMeansPoint(current)) {
        QModelIndex img = current.parent();
        emit currentPointChanged(img.row(), current.row());
    }
}

Point2DModel *Point2DView::getPoint2DModel()
{
    return this->point2DModel;
}
