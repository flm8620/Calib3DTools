#ifndef DOUBLESPINDELEGATE_H
#define DOUBLESPINDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class DoubleSpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    DoubleSpinDelegate(QObject *parent = 0): QStyledItemDelegate(parent){}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void setEditorData(QWidget *editor, const QModelIndex &index) const Q_DECL_OVERRIDE;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const Q_DECL_OVERRIDE;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // DOUBLESPINDELEGATE_H
