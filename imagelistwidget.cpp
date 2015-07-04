#include "imagelistwidget.h"
#include <QtWidgets>
ImageListWidget::ImageListWidget(const QString &label, QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *loadButton = new QPushButton(tr("Load"));
    QPushButton *saveButton = new QPushButton(tr("Save"));
    QPushButton *clearButton = new QPushButton(tr("Clear"));
    QPushButton *upButton = new QPushButton(tr("^"));
    QPushButton *downButton = new QPushButton(tr("v"));
    QPushButton *deleteButton = new QPushButton(tr("-"));
    QHBoxLayout *bLay = new QHBoxLayout;
    loadButton->setMaximumWidth(40);
    clearButton->setMaximumWidth(40);
    upButton->setMaximumWidth(20);
    downButton->setMaximumWidth(20);
    deleteButton->setMaximumWidth(20);
    bLay->addWidget(loadButton);
    bLay->addWidget(saveButton);
    bLay->addWidget(clearButton);
    bLay->addWidget(upButton);
    bLay->addWidget(downButton);
    bLay->addWidget(deleteButton);
    this->view = new ImageListView;
    layout->addLayout(bLay);
    layout->addWidget(this->view);

    connect(loadButton, SIGNAL(clicked(bool)), view, SLOT(onOpenImage()));
    connect(saveButton,SIGNAL(clicked(bool)),view,SLOT(onSaveImage()));
    connect(clearButton,SIGNAL(clicked(bool)),view,SLOT(clear()));
    connect(upButton, SIGNAL(clicked(bool)), view, SLOT(moveUp()));
    connect(downButton, SIGNAL(clicked(bool)), view, SLOT(moveDown()));
    connect(deleteButton, SIGNAL(clicked(bool)), view, SLOT(deleteImage()));
    QGroupBox *groupBox = new QGroupBox(label);
    groupBox->setLayout(layout);
    QHBoxLayout *boxLayout = new QHBoxLayout;
    boxLayout->addWidget(groupBox);
    setLayout(boxLayout);
}

void ImageListWidget::setModel(ImageListModel *model)
{
    this->view->setModel(model);
}

ImageListView *ImageListWidget::getView()
{
    return this->view;
}
