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
    void openImage();
    void deleteImage();
    void moveUp();
    void moveDown();
    void openInViewer();
    void clear();
private slots:
    void imageClicked(QModelIndex index);
signals:
    void imageToDisplay(QImage image);
private:

    bool loadImage(const QStringList &list);
    ImageListModel *imageModel;
};

#endif // IMAGELISTVIEW_H
