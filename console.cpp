#include "console.h"

Console::Console(QWidget *parent) :
    QTextEdit(parent)
{
    setReadOnly(true);
}

Console &Console::operator<<(const char *s)
{
    append(tr(s));

    return *this;
}

void Console::messageReceiver(QString s, libMsg::MessageType msgType)
{
    // QTextCursor prev_cursor = this->textCursor();
    this->moveCursor(QTextCursor::End);
    switch (msgType) {
    case libMsg::M_TEXT:
        this->insertPlainText(s);
        break;
    case libMsg::M_INFO:
        this->append(s);
        break;
    case libMsg::M_WARN:
        this->append(tr("<font color='green'><b>")+s+tr("</b></font>"));
        break;
    case libMsg::M_ERROR:
        this->append(tr("<font color='red'><b>")+s+tr("</b></font>"));
        break;
    }
    // this->setTextCursor(prev_cursor);
}
