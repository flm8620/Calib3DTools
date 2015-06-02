#include "imagelistwidget.h"
#include "imagelistview.h"
#include <QtWidgets>
ImageListWidget::ImageListWidget(const QString &label, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout=new QVBoxLayout;
    QPushButton* loadButton=new QPushButton(tr("Load"));
    QPushButton* upButton=new QPushButton(tr("^"));
    QPushButton* downButton=new QPushButton(tr("v"));
    QPushButton* deleteButton=new QPushButton(tr("-"));
    QPushButton* viewerButton=new QPushButton(tr("View..."));
    QHBoxLayout* bLay=new QHBoxLayout;
    loadButton->setMaximumWidth(40);
    upButton->setMaximumWidth(20);
    downButton->setMaximumWidth(20);
    deleteButton->setMaximumWidth(20);
    viewerButton->setMaximumWidth(50);
    bLay->addWidget(loadButton);
    bLay->addSpacing(10);
    bLay->addWidget(upButton);
    bLay->addWidget(downButton);
    bLay->addWidget(deleteButton);
    bLay->addWidget(viewerButton);
    view=new ImageListView;
    layout->addLayout(bLay);
    layout->addWidget(view);

    connect(loadButton,SIGNAL(clicked(bool)),view,SLOT(openImage()));
    connect(upButton,SIGNAL(clicked(bool)),view,SLOT(moveUp()));
    connect(downButton,SIGNAL(clicked(bool)),view,SLOT(moveDown()));
    connect(deleteButton,SIGNAL(clicked(bool)),view,SLOT(deleteImage()));
    connect(viewerButton,SIGNAL(clicked(bool)),view,SLOT(openInViewer()));
    QGroupBox *groupBox=new QGroupBox(label);
    groupBox->setLayout(layout);
    QHBoxLayout* boxLayout=new QHBoxLayout;
    boxLayout->addWidget(groupBox);
    setLayout(boxLayout);
}

void ImageListWidget::setModel(QAbstractListModel *model)
{
    view->setModel(model);
}

