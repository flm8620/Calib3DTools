#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QTextEdit>
class Console : public QTextEdit
{
    Q_OBJECT
public:
    Console(QWidget* parent=0);
    Console& operator <<(const char* s);
    void warning(const char* s);
};

#endif // CONSOLE_H
