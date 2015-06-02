#include "point3dwidget.h"
#include "point3dmodel.h"
#include <QTableView>
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
Point3DWidget::Point3DWidget(QWidget *parent) : QWidget(parent)
{
    view=new QTableView(this);
    QPushButton *addPointButton=new QPushButton(tr("Add Point"));
    QPushButton *removePointButton=new QPushButton(tr("Remove Point"));
    QHBoxLayout* bLay=new QHBoxLayout;
    bLay->addWidget(addPointButton);
    bLay->addWidget(removePointButton);

    connect(addPointButton,SIGNAL(clicked(bool)),this,SLOT(addPoint()));
    connect(removePointButton,SIGNAL(clicked(bool)),this,SLOT(removePoint()));

    QVBoxLayout* hLay=new QVBoxLayout;
    hLay->addLayout(bLay);
    hLay->addWidget(view);
    QGroupBox* groupBox=new QGroupBox(tr("Point 3D"));
    groupBox->setLayout(hLay);
    QHBoxLayout* lay=new QHBoxLayout;
    lay->addWidget(groupBox);
    setLayout(lay);
}

void Point3DWidget::setModel(Point3DModel *model)
{
    this->model=model;
    view->setModel(model);
}


void Point3DWidget::addPoint()
{
    QStandardItem *item1=new QStandardItem("0");
    QStandardItem *item2=new QStandardItem("0");
    QStandardItem *item3=new QStandardItem("0");
    QList<QStandardItem*> list;
    list.append(item1);
    list.append(item2);
    list.append(item3);
    model->appendRow(list);
}

void Point3DWidget::removePoint()
{
    QItemSelection s=view->selectionModel()->selection();
    if(s.isEmpty())return;
    QModelIndex sId= s.first().indexes().first();
    model->removeRow(sId.row());
    view->selectionModel()->select(sId,QItemSelectionModel::ClearAndSelect);
}

void Point3DWidget::moveUp()
{

}

void Point3DWidget::moveDown()
{

}
