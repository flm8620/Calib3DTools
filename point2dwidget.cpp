#include "point2dwidget.h"
#include "point2dview.h"
#include "point2dmodel.h"
#include <QPushButton>
#include <QLayout>
#include <QGroupBox>
#include <QDebug>
Point2DWidget::Point2DWidget(QWidget *parent) : QWidget(parent)
{
    view = new Point2DView(this);
    QPushButton *addPointButton = new QPushButton(tr("+"));
    QPushButton *removePointButton = new QPushButton(tr("-"));
    QPushButton *moveUpButton = new QPushButton(tr("^"));
    QPushButton *moveDownButton = new QPushButton(tr("v"));
    QHBoxLayout *bLay = new QHBoxLayout;
    addPointButton->setMaximumWidth(20);
    removePointButton->setMaximumWidth(20);
    moveUpButton->setMaximumWidth(20);
    moveDownButton->setMaximumWidth(20);
    bLay->addWidget(moveUpButton);
    bLay->addWidget(moveDownButton);
    bLay->addWidget(addPointButton);
    bLay->addWidget(removePointButton);

    connect(addPointButton, SIGNAL(clicked(bool)), this, SLOT(addPoint()));
    connect(removePointButton, SIGNAL(clicked(bool)), this, SLOT(removePoint()));
    connect(moveUpButton,SIGNAL(clicked(bool)),this,SLOT(moveUp()));
    connect(moveDownButton,SIGNAL(clicked(bool)),this,SLOT(moveDown()));

    QVBoxLayout *hLay = new QVBoxLayout;
    hLay->addLayout(bLay);
    hLay->addWidget(view);

    QGroupBox *groupBox = new QGroupBox(tr("Point 2D"));
    groupBox->setLayout(hLay);
    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(groupBox);
    setLayout(lay);
}

void Point2DWidget::setModel(Point2DModel *model)
{
    this->model = model;
    view->setPoint2DModel(model);
}

Point2DView *Point2DWidget::getPoint2DView()
{
    return this->view;
}

void Point2DWidget::addPoint()
{
    this->model->appendPoint();
}

void Point2DWidget::removePoint()
{
    QModelIndex sId = this->getFirstSelectedItem();
    this->model->removePoint(sId);
}

void Point2DWidget::moveUp()
{
    QModelIndex index=this->getFirstSelectedItem();
    this->model->movePointUp(index);
    QModelIndex id = this->model->index(index.row()-1,index.column(),index.parent());
    this->view->selectionModel()->select(id,QItemSelectionModel::ClearAndSelect);
}

void Point2DWidget::moveDown()
{
    QModelIndex index=this->getFirstSelectedItem();
    this->model->movePointDown(index);
    QModelIndex id = this->model->index(index.row()+1,index.column(),index.parent());
    this->view->selectionModel()->select(id,QItemSelectionModel::ClearAndSelect);
}

QModelIndex Point2DWidget::getFirstSelectedItem()
{
    QItemSelection s = view->selectionModel()->selection();
    if (!s.isEmpty())
        return s.first().indexes().first();
    return QModelIndex();
}
