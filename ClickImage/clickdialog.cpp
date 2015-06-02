#include "clickdialog.h"
#include "controllertableview.h"
#include "markerimageview.h"
#include <QtWidgets>
#include <QDebug>
ClickDialog::ClickDialog(const QImage &image, const QList<double>& coords, QWidget *parent)
    :QDialog(parent)
{
    model= new QStandardItemModel(this);
    tableView=new ControllerTableView(this);
    tableView->setModel(model);
    markerImageView= new MarkerImageView;
    markerImageView->setModel(model);
    markerImageView->setSelectionModel(tableView->selectionModel());
    markerImageView->loadImage(image);
    initModel(coords);
    connect(markerImageView,SIGNAL(markerInsertedOnScreen()),this,SLOT(markerInsertedOnScreen()));

    QDialogButtonBox *buttonBox=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));


    QFrame* controlPanel=createControlPanel();
    markerImageView->setMinimumSize(400,400);
    QHBoxLayout *thisLayout=new QHBoxLayout;
    thisLayout->addWidget(markerImageView);
    thisLayout->addWidget(controlPanel);
    QVBoxLayout* layout=new QVBoxLayout;
    layout->addLayout(thisLayout);
    layout->addWidget(buttonBox);

    setLayout(layout);

}

QList<double> ClickDialog::getResult()
{
    QList<double> coords;
    int rows=model->rowCount();
    for(int i=0;i<rows;++i){
        QStandardItem* itemX=model->item(i,0);
        QStandardItem* itemY=model->item(i,1);
        coords.append(itemX->text().toDouble());
        coords.append(itemY->text().toDouble());
    }
    return coords;
}

void ClickDialog::initModel(const QList<double>& coords)
{
    int n=coords.size()/2;
    int j=0;
    for(int i=0;i<n;++i){
        QList<QStandardItem*> list;
        list.append(new QStandardItem(QString::number(coords.value(j))));
        j++;
        list.append(new QStandardItem(QString::number(coords.value(j))));
        j++;
        model->appendRow(list);
    }
}

QFrame *ClickDialog::createControlPanel()
{
    QFrame* frame=new QFrame;

    QPushButton *upButton=new QPushButton(tr("^"));
    QPushButton *downButton=new QPushButton(tr("V"));
    placeButton=new QPushButton(tr("pickOnScreen"));
    placeButton->setCheckable(true);



    downButton->setMinimumWidth(10);
    upButton->setMinimumWidth(10);


    connect(placeButton,SIGNAL(toggled(bool)),this,SLOT(getOnScreenToggled(bool)));
    connect(upButton,SIGNAL(clicked(bool)),tableView,SLOT(moveUp()));
    connect(downButton,SIGNAL(clicked(bool)),tableView,SLOT(moveDown()));
    QHBoxLayout *buttonsLayout=new QHBoxLayout;
    buttonsLayout->addWidget(placeButton);
    buttonsLayout->addWidget(upButton);
    buttonsLayout->addWidget(downButton);
    QVBoxLayout *thisLayout=new QVBoxLayout;
    thisLayout->addLayout(buttonsLayout);
    thisLayout->addWidget(tableView);
    frame->setLayout(thisLayout);
    return frame;
}

void ClickDialog::getOnScreenToggled(bool toggle)
{
    if(toggle){
        markerImageView->setMode(MarkerImageView::InsertItem);
    }else{
        markerImageView->setMode(MarkerImageView::MoveItem);
    }
}

void ClickDialog::markerInsertedOnScreen()
{
    placeButton->setChecked(false);
}

