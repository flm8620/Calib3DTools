#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QtWidgets>
#include "console.h"
class ConsoleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget *parent = 0);
    Console* getConsole();
    QPushButton *getAbortButton();
signals:

public slots:
private:
    QPushButton *abortButton;
    Console* console;
};

#endif // CONSOLEWIDGET_H
