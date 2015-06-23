#ifndef IMAGELISTWIDGET_H
#define IMAGELISTWIDGET_H

#include <QWidget>
#include "imagelistmodel.h"
#include "imagelistview.h"
class QString;
class ImageListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageListWidget(const QString& label,QWidget *parent = 0);
    void setModel(ImageListModel* model);
    ImageListView* getView();
signals:

public slots:
private:
    ImageListView* view;
};

#endif // IMAGELISTWIDGET_H
