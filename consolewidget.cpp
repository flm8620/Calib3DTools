#include "consolewidget.h"

ConsoleWidget::ConsoleWidget( QWidget *parent) : QWidget(parent)
{

    QPushButton *clear=new QPushButton(tr("Clear"));
    QPushButton *save=new QPushButton(tr("Save As"));
    this->abortButton=new QPushButton(tr("STOP"));
    QHBoxLayout *bLay=new QHBoxLayout;
    bLay->addWidget(new QLabel(tr("Console")));
    bLay->addWidget(clear);
    bLay->addWidget(save);
    bLay->addWidget(this->abortButton);
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

QPushButton *ConsoleWidget::getAbortButton()
{
    return this->abortButton;
}

