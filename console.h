#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextEdit>
#include "messager.h"
class Console : public QTextEdit
{
    Q_OBJECT
public:
    Console(QWidget* parent=0);
    Console& operator <<(const char* s);
public slots:
    void messageReceiver(QString s, libMsg::MessageType msgType=libMsg::M_TEXT);
};

#endif // CONSOLE_H
