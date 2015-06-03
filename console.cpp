#include "console.h"

Console::Console(QWidget *parent)
    :QTextEdit(parent)
{
    setReadOnly(true);
}

Console &Console::operator<<(const char *s)
{
    append(tr(s));

    return *this;
}

void Console::warning(const char *s)
{
    QString st(s);
    append(tr("<font color='red'><b>")+st+tr("</b></font>"));
}

void Console::messageReceiver(QString s, bool warning)
{
    if(warning){
        append(tr("<font color='red'><b>")+s+tr("</b></font>"));
    }else{
        append(s);
    }
}

