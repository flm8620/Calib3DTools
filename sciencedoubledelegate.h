#ifndef DOUBLESPINDELEGATE_H
#define DOUBLESPINDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include "qsciencespinbox.h"
class ScienceDoubleDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    ScienceDoubleDelegate(QObject *parent = 0): QStyledItemDelegate(parent),precision(8){}
    void setPrecision(int precision);
    QString displayText(const QVariant &value, const QLocale &locale) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
public:
    int precision;
};

#endif // DOUBLESPINDELEGATE_H
