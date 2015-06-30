#include "consolewidget.h"
#include <QtWidgets>
ConsoleWidget::ConsoleWidget( QWidget *parent) : QWidget(parent)
{

    QPushButton *clear=new QPushButton(tr("Clear"));
    QPushButton *save=new QPushButton(tr("Save As"));
    QHBoxLayout *bLay=new QHBoxLayout;
    bLay->addWidget(new QLabel(tr("Console")));
    bLay->addWidget(clear);
    bLay->addWidget(save);
    this->console=new Console;
    QVBoxLayout *layout=new QVBoxLayout;
    layout->addLayout(bLay);
    layout->addWidget(console);
    connect(clear,SIGNAL(clicked(bool)),this->console,SLOT(clear()));
    connect(save,SIGNAL(clicked(bool)),this->console,SLOT(saveHtml()));
    this->setLayout(layout);
}

Console *ConsoleWidget::getConsole()
{
    return this->console;
}

