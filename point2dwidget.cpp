#include "point2dwidget.h"
#include "point2dview.h"
#include "point2dmodel.h"
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QDebug>
Point2DWidget::Point2DWidget(QWidget *parent) : QWidget(parent)
{
    view=new Point2DView(this);
    QPushButton *editButton=new QPushButton(tr("Edit..."));
    QPushButton *addPointButton=new QPushButton(tr("Add Point"));
    QPushButton *removePointButton=new QPushButton(tr("Remove Point"));
    QVBoxLayout* bLay=new QVBoxLayout;
    bLay->addWidget(editButton);
    bLay->addWidget(addPointButton);
    bLay->addWidget(removePointButton);

    connect(editButton,SIGNAL(clicked(bool)),this,SLOT(editInViewer()));
    connect(addPointButton,SIGNAL(clicked(bool)),this,SLOT(addPoint()));
    connect(removePointButton,SIGNAL(clicked(bool)),this,SLOT(removePoint()));

    QHBoxLayout* hLay=new QHBoxLayout;
    hLay->addWidget(view);
    hLay->addLayout(bLay);
    QGroupBox* groupBox=new QGroupBox(tr("Point 2D"));
    groupBox->setLayout(hLay);
    QHBoxLayout* lay=new QHBoxLayout;
    lay->addWidget(groupBox);
    setLayout(lay);
}

void Point2DWidget::setModel(Point2DModel *model)
{
    this->model=model;
    view->setModel(model);
}

void Point2DWidget::editInViewer()
{
    QStandardItem *item1=new QStandardItem(tr("Image"));
    QStandardItem *item2=new QStandardItem();
    QStandardItem *item3=new QStandardItem();
    QList<QStandardItem*> list;
    list.append(item1);
    list.append(item2);
    list.append(item3);
    model->appendRow(list);
}

void Point2DWidget::addPoint()
{
    int n=model->rowCount();

    for(int i=0;i<n;++i){
        QStandardItem *parentItem=model->invisibleRootItem()->child(i);
        int pointCount=parentItem->rowCount();
        QStandardItem *item1=new QStandardItem(tr("Point"));
        QStandardItem *item2=new QStandardItem("0");
        QStandardItem *item3=new QStandardItem("0");
        QList<QStandardItem*> list;
        list.append(item1);
        list.append(item2);
        list.append(item3);
        parentItem->appendRow(list);
    }
}

void Point2DWidget::removePoint()
{
    QItemSelection s=view->selectionModel()->selection();
    if(s.isEmpty())return;
    QModelIndex sId= s.first().indexes().first();
    QStandardItem* item=model->itemFromIndex(sId);
    if(item->parent()==model->invisibleRootItem())return;
    int row=item->row();
    int n=model->rowCount();
    for(int i=0;i<n;++i){
        QStandardItem* parent=model->item(i);
        parent->removeRow(row);
    }
}

void Point2DWidget::moveUp()
{

}

void Point2DWidget::moveDown()
{

}

