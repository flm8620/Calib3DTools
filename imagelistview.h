#ifndef IMAGELISTVIEW_H
#define IMAGELISTVIEW_H

#include <QObject>
#include <QWidget>
#include <QListView>
#include "imagelistmodel.h"
class ImageListView : public QListView
{
    Q_OBJECT
public:
    ImageListView(QWidget* parent=0);
    void setModel(ImageListModel *model);
public slots:
    void onOpenImage();
    void onSaveImage();
    void deleteImage();
    void moveUp();
    void moveDown();
    void clear();
private slots:
    void imageClicked(QModelIndex index);
signals:
    void imageToDisplay(QImage image);
private:
    bool openImage(const QStringList &list);
    bool saveImage(const QStringList &list);
    ImageListModel *imageModel;
};

#endif // IMAGELISTVIEW_H
