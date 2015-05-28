#ifndef IMAGELISTWIDGET_H
#define IMAGELISTWIDGET_H

#include <QWidget>
class ImageListView;
class QAbstractListModel;
class ImageListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageListWidget(QWidget *parent = 0);
    void setModel(QAbstractListModel* model);
signals:

public slots:
private:
    ImageListView* view;
};

#endif // IMAGELISTWIDGET_H
