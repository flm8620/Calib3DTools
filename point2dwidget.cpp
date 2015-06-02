#include "point2dwidget.h"
#include "point2dview.h"
#include "point2dmodel.h"
#include "ClickImage/clickdialog.h"
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QDebug>
Point2DWidget::Point2DWidget(QWidget *parent) : QWidget(parent)
{
    view=new Point2DView(this);
    QPushButton *editButton=new QPushButton(tr("Edit..."));
    QPushButton *addPointButton=new QPushButton(tr("+ Point"));
    QPushButton *removePointButton=new QPushButton(tr("- Point"));
    QHBoxLayout* bLay=new QHBoxLayout;
    bLay->addWidget(editButton);
    bLay->addWidget(addPointButton);
    bLay->addWidget(removePointButton);

    connect(editButton,SIGNAL(clicked(bool)),this,SLOT(editInViewer()));
    connect(addPointButton,SIGNAL(clicked(bool)),this,SLOT(addPoint()));
    connect(removePointButton,SIGNAL(clicked(bool)),this,SLOT(removePoint()));

    QVBoxLayout* hLay=new QVBoxLayout;
    hLay->addLayout(bLay);
    hLay->addWidget(view);

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
    QItemSelection s=view->selectionModel()->selection();
    if(s.isEmpty())return;
    QModelIndex sId= s.first().indexes().first();
    QStandardItem* item=model->itemFromIndex(sId);
    if(item->parent()!=0){
        item=item->parent();
    }

    int rows=item->rowCount();
    if(rows==0)return;
    QList<double> coords;
    for(int i=0;i<rows;++i){
        QStandardItem* childX=item->child(i,1);
        QStandardItem* childY=item->child(i,2);
        coords.append(childX->text().toDouble());
        coords.append(childY->text().toDouble());
    }
    QImage image=model->getImage(item->row());
    ClickDialog dialog(image,coords,this);
    if(dialog.exec()){
        coords=dialog.getResult();
        Q_ASSERT(coords.size()/2==rows);
        int j=0;
        for(int i=0;i<rows;++i){
            item->child(i,1)->setText(QString::number(coords.value(j)));
            ++j;
            item->child(i,2)->setText(QString::number(coords.value(j)));
            ++j;
        }
    }


}

void Point2DWidget::addPoint()
{
    int n=model->rowCount();

    for(int i=0;i<n;++i){
        QStandardItem *parentItem=model->invisibleRootItem()->child(i);
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

