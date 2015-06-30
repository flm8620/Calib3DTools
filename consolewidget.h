#ifndef CONSOLEWIDGET_H
#define CONSOLEWIDGET_H

#include <QWidget>
#include "console.h"
class ConsoleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConsoleWidget(QWidget *parent = 0);
    Console* getConsole();
signals:

public slots:
private:
    Console* console;
};

#endif // CONSOLEWIDGET_H
