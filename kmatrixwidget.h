#ifndef KMATRIXWIDGET_H
#define KMATRIXWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "kmatrixmodel.h"
class KMatrixWidget : public QWidget
{
    Q_OBJECT
public:
    explicit KMatrixWidget(QWidget *parent = 0);
    void setModel(KMatrixModel *model);
    QTableView *getView();
public slots:
    void saveFile();
    void loadFile();
    void clear();
private:
    bool saveKMatrix(const QStringList& list);
    bool loadKMatrix(const QStringList& list);
private:
    QTableView *view;
    KMatrixModel *model;
};

#endif // KMATRIXWIDGET_H
