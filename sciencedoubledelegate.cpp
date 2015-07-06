#include "sciencedoubledelegate.h"
#include <QDebug>
void ScienceDoubleDelegate::setPrecision(int precision)
{
    precision=std::max(std::min(precision,15),3);
    this->precision=precision;
}

QString ScienceDoubleDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    bool isDouble=false;
    value.toDouble(&isDouble);
    if(isDouble)
        return QString::number(value.toDouble(), 'g', this->precision);
    else
        return value.toString();
}

QWidget *ScienceDoubleDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                                             const QModelIndex &index) const
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
    QScienceSpinBox *spinBox = static_cast<QScienceSpinBox *>(editor);
    spinBox->setDecimals(15);
    spinBox->setValue(value);
}

void ScienceDoubleDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                         const QModelIndex &index) const
{
    QScienceSpinBox *spinBox = static_cast<QScienceSpinBox *>(editor);
    spinBox->interpretText();
    double value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void ScienceDoubleDelegate::updateEditorGeometry(QWidget *editor,
                                                 const QStyleOptionViewItem &option,
                                                 const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
