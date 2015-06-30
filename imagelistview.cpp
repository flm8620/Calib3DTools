#include "imagelistview.h"
#include "imageviewer.h"
#include <QMessageBox>
#include <QImage>
#include <QFileInfo>
#include <QFileDialog>

ImageListView::ImageListView(QWidget *parent) :
    QListView(parent)
{
}

void ImageListView::setModel(ImageListModel *model)
{
    this->imageModel = model;
    QListView::setModel(model);
}

void ImageListView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    int row=current.row();
    QImage image=this->imageModel->core()->getImage(row);
    emit imageToDisplay(image);
    QListView::currentChanged(current,previous);
}

void ImageListView::openImage()
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
        if (loadImage(dialog.selectedFiles())) break;
}

bool ImageListView::loadImage(const QStringList &list)
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

void ImageListView::deleteImage()
{
    QModelIndexList idList = selectionModel()->selectedRows();
    if (idList.isEmpty()) return;
    int row = idList.first().row();
    this->imageModel->deleteImage(row);
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

void ImageListView::openInViewer()
{
    QModelIndexList idList = selectionModel()->selectedRows();
    if (idList.isEmpty()) return;
    int row = idList.first().row();
    QAbstractItemModel *m = model();
    QModelIndex id = m->index(row, 0);
    QImage image = qvariant_cast<QImage>(m->data(id, Qt::UserRole));
    Q_ASSERT(!image.isNull());
    ImageViewer *viewer = new ImageViewer(image, this);
    viewer->setWindowFlags(Qt::Window);
    viewer->show();
}

void ImageListView::clear()
{
    this->imageModel->clear();
}
