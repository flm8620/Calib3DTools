#include "sciencedoubledelegate.h"
#include <QDebug>
QString ScienceDoubleDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    return QString::number(value.toDouble(),'g',15);
}

QWidget *ScienceDoubleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    QScienceSpinBox *editor = new QScienceSpinBox(parent);
    editor->setFrame(false);
    editor->setDecimals(15);
    return editor;
}

void ScienceDoubleDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    bool ok;
    double value = index.model()->data(index, Qt::EditRole).toDouble(&ok);
    QScienceSpinBox *spinBox = static_cast<QScienceSpinBox*>(editor);
    spinBox->setDecimals(15);
    spinBox->setValue(value);
}

void ScienceDoubleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QScienceSpinBox *spinBox = static_cast<QScienceSpinBox*>(editor);
    spinBox->interpretText();
    double value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void ScienceDoubleDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
