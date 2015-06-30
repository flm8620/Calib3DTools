#include "console.h"
#include <QFileDialog>
#include <QSaveFile>
#include <QMessageBox>
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
    this->moveCursor(QTextCursor::End);
    switch (msgType) {
    case libMsg::M_TEXT:
        this->setFontWeight(QFont::Normal);
        this->setTextColor(Qt::black);
        this->insertPlainText(s);
        break;
    case libMsg::M_INFO:
        this->setFontWeight(QFont::Bold);

        this->insertPlainText(s+"\n");
        this->setFontWeight(QFont::Normal);
        break;
    case libMsg::M_WARN:
        this->setFontWeight(QFont::Bold);
        this->setTextColor(Qt::darkYellow);
        this->insertPlainText(s+"\n");
        this->setTextColor(Qt::black);
        this->setFontWeight(QFont::Normal);
        break;
    case libMsg::M_ERROR:
        this->setFontWeight(QFont::Bold);
        this->setTextColor(Qt::red);
        this->insertPlainText(s+"\n");
        this->setTextColor(Qt::black);
        this->setFontWeight(QFont::Normal);
        break;
    }
}

void Console::saveHtml()
{
    QString content = this->toHtml();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
    if (fileName.isEmpty()) return;
    QSaveFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(this, "Error", tr("Cannot open %1").arg(fileName));
        return;
    }
    file.write(content.toUtf8());
    file.commit();
}
