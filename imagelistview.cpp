#include "imagelistview.h"
#include "imageviewer.h"
#include "messager.h"
#include <QMessageBox>
#include <QImage>
#include <QFileInfo>
#include <QFileDialog>

ImageListView::ImageListView(QWidget *parent) :
    QListView(parent)
{
    connect(this, SIGNAL(clicked(QModelIndex)), this, SLOT(imageClicked(QModelIndex)));
}

void ImageListView::setModel(ImageListModel *model)
{
    this->imageModel = model;
    QListView::setModel(model);
}

void ImageListView::onOpenImage()
{
    QFileDialog dialog(this, tr("Open Image"), QDir::currentPath());
    // QStringList formatList;
    QStringList filters;
    filters << "Image files (*.png *.bmp *.jpg *.jpeg)"
            << "Any files (*)";

    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    // dialog.setMimeTypeFilters(formatList);
    dialog.setNameFilters(filters);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    while (dialog.exec() == QDialog::Accepted)
        if (openImage(dialog.selectedFiles())) break;
}

void ImageListView::onSaveImage()
{
    QFileDialog dialog(this, tr("Save Image"), QDir::currentPath());
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    while (dialog.exec() == QDialog::Accepted)
        if (saveImage(dialog.selectedFiles())) break;
}

bool ImageListView::openImage(const QStringList &list)
{
    QString filePath;
    foreach (filePath, list) {
        QImage image(filePath);
        if (image.isNull()) {
            QMessageBox::information(this, "Error", tr("Cannot load %1").arg(filePath));
            return false;
        }
    }

    foreach (filePath, list) {
        QFileInfo info(filePath);
        QString name = info.fileName();
        QImage image(filePath);
        this->imageModel->appendImage(name, image);
    }
    return true;
}

bool ImageListView::saveImage(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString path = list.first();

    QList<QPair<QString, QImage> > imageList;
    this->imageModel->core()->getContent(imageList);
    for (int i = 0; i < imageList.size(); ++i) {
        QString name = imageList[i].first;
        QString filepath = QDir(path).filePath(name);
        QString suffix = QFileInfo(filepath).suffix().toLower();
        if (suffix != tr("jpg") && suffix != tr("jpeg") && suffix != tr("bmp")) {
            name = name+tr(".bmp");
        }
        QImageWriter writer(QDir(path).filePath(name));
        if (!writer.write(imageList[i].second)) {
            libMsg::cout<<"failed to save image: "<<QDir(path).filePath(name).toStdString()
                        <<libMsg::endl;
            libMsg::cout<<writer.errorString().toStdString()<<libMsg::endl;
        }
    }
    return true;
}

void ImageListView::deleteImage()
{
    QModelIndexList idList = selectionModel()->selectedRows();
    if (idList.isEmpty()) return;
    int row = idList.first().row();
    this->imageModel->deleteImage(row);
    this->selectionModel()->select(idList.first(),QItemSelectionModel::ClearAndSelect);
}

void ImageListView::moveUp()
{
    QModelIndexList idList = selectionModel()->selectedRows();
    if (idList.isEmpty()) return;
    int row = idList.first().row();
    QAbstractItemModel *m = model();
    if (row <= 0 || row >= m->rowCount()) return;
    this->imageModel->moveUp(row);
    QModelIndex id = m->index(row-1, 0);
    selectionModel()->select(id, QItemSelectionModel::ClearAndSelect);
}

void ImageListView::moveDown()
{
    QModelIndexList idList = selectionModel()->selectedRows();
    if (idList.isEmpty()) return;
    int row = idList.first().row();
    QAbstractItemModel *m = model();
    if (row < 0 || row >= m->rowCount()-1) return;
    this->imageModel->moveDown(row);
    QModelIndex id = m->index(row+1, 0);
    selectionModel()->select(id, QItemSelectionModel::ClearAndSelect);
}

void ImageListView::clear()
{
    this->imageModel->clear();
}

void ImageListView::imageClicked(QModelIndex index)
{
    int row = index.row();
    QImage image = this->imageModel->core()->getImage(row);
    emit imageToDisplay(image);
}
