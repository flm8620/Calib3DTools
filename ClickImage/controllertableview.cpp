#include "controllertableview.h"
ControllerTableView::ControllerTableView(QWidget *parent)
    :QTableView(parent)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
}

void ControllerTableView::addOneItem()
{
    QAbstractItemModel *itemModel=model();
    if(itemModel==0)return;
    QItemSelectionModel *sModel=selectionModel();
    QModelIndexList list= sModel->selectedRows();
    int row;
    if(list.isEmpty())row=itemModel->rowCount();
    else row=list.first().row();
    Q_ASSERT(row>=0 && row<=itemModel->rowCount());
    itemModel->insertRow(row);
    QModelIndex xIndex=itemModel->index(row,0);
    QModelIndex yIndex=itemModel->index(row,1);
    itemModel->setData(xIndex,0.0);
    itemModel->setData(yIndex,0.0);
}

void ControllerTableView::removeOneItem()
{
    QAbstractItemModel *itemModel=model();
    if(itemModel==0)return;
    QItemSelectionModel *sModel=selectionModel();
    QModelIndexList list= sModel->selectedRows();
    if(list.isEmpty())return;

    int row=list.first().row();
    Q_ASSERT(row>=0 && row<itemModel->rowCount());
    itemModel->removeRow(row);
}

void ControllerTableView::moveUp()
{
    QAbstractItemModel *itemModel=model();
    if(itemModel==0)return;
    QItemSelectionModel *sModel=selectionModel();
    QModelIndexList list= sModel->selectedRows();
    if(list.isEmpty())return;

    int row=list.first().row();
    Q_ASSERT(row>=0 && row<itemModel->rowCount());
    if(row==0)return;
    QModelIndex index1=itemModel->index(row,0);
    QModelIndex index2=itemModel->index(row,1);
    QVariant x=itemModel->data(index1);
    QVariant y=itemModel->data(index2);
    itemModel->removeRow(row);
    itemModel->insertRow(row-1);
    QModelIndex newIndex1=itemModel->index(row-1,0);
    QModelIndex newIndex2=itemModel->index(row-1,1);
    itemModel->setData(newIndex1,x);
    itemModel->setData(newIndex2,y);

    QItemSelection itemSelection;
    itemSelection.append(QItemSelectionRange(newIndex1,newIndex2));
    sModel->select(itemSelection,QItemSelectionModel::ClearAndSelect);
}

void ControllerTableView::moveDown()
{
    QAbstractItemModel *itemModel=model();
    if(itemModel==0)return;
    QItemSelectionModel *sModel=selectionModel();
    QModelIndexList list= sModel->selectedRows();
    if(list.isEmpty())return;

    int row=list.first().row();
    Q_ASSERT(row>=0 && row<itemModel->rowCount());
    if(row==itemModel->rowCount()-1)return;
    QModelIndex index1=itemModel->index(row,0);
    QModelIndex index2=itemModel->index(row,1);
    QVariant x=itemModel->data(index1);
    QVariant y=itemModel->data(index2);
    itemModel->removeRow(row);
    itemModel->insertRow(row+1);
    QModelIndex newIndex1=itemModel->index(row+1,0);
    QModelIndex newIndex2=itemModel->index(row+1,1);
    itemModel->setData(newIndex1,x);
    itemModel->setData(newIndex2,y);

    QItemSelection itemSelection;
    itemSelection.append(QItemSelectionRange(newIndex1,newIndex2));
    sModel->select(itemSelection,QItemSelectionModel::ClearAndSelect);
}
