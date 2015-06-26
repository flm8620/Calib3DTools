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

    connect(addPointButton,SIGNAL(clicked(bool)),this,SLOT(appendPoint()));
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


void Point3DWidget::appendPoint()
{
    this->model->append();
}

void Point3DWidget::removePoint()
{
    QModelIndex index= this->getFirstSelectedItem();
    model->removeRow(index.row());
    view->selectionModel()->select(index,QItemSelectionModel::ClearAndSelect);
}

void Point3DWidget::moveUp()
{
    QModelIndex index= this->getFirstSelectedItem();
    this->model->moveUp(index);
}

void Point3DWidget::moveDown()
{
    QModelIndex index= this->getFirstSelectedItem();
    this->model->moveDown(index);
}

QModelIndex Point3DWidget::getFirstSelectedItem()
{
    QItemSelection s = view->selectionModel()->selection();
    if (!s.isEmpty())
        return s.first().indexes().first();
    return QModelIndex();
}
