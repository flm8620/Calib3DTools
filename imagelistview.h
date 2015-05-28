#ifndef IMAGELISTVIEW_H
#define IMAGELISTVIEW_H

#include <QObject>
#include <QWidget>
#include <QListView>
class ImageViewer;
class ImageListView : public QListView
{
    Q_OBJECT
public:
    ImageListView(QWidget* parent=0);
public slots:
    void openImage();
    void deleteImage();
    void moveUp();
    void moveDown();
    void openInViewer();
private:
    void addImage(const QString& string, QImage image);
    bool loadImage(const QStringList &list);
};

#endif // IMAGELISTVIEW_H
