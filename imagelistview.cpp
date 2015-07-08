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
    QSettings settings;
    QFileDialog dialog(this, tr("Open Image"), settings.value("default_dir").toString());
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
    if(!dialog.selectedFiles().isEmpty()){
        settings.setValue("default_dir",dialog.selectedFiles().first());
    }
}

void ImageListView::onSaveImage()
{
    QSettings settings;
    QFileDialog dialog(this, tr("Save Image"), settings.value("default_dir").toString());
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOption(QFileDialog::ShowDirsOnly, true);
    while (dialog.exec() == QDialog::Accepted)
        if (saveImage(dialog.selectedFiles())) break;
    if(!dialog.selectedFiles().isEmpty()){
        settings.setValue("default_dir",dialog.selectedFiles().first());
    }
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
    QModelIndex index = this->getFirstSelectedItem();
    this->imageModel->deleteImage(index.row());
    this->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
}

void ImageListView::moveUp()
{
    QModelIndex index = this->getFirstSelectedItem();
    this->imageModel->moveUp(index);
    if (index.row() > 0) {
        QModelIndex id = this->imageModel->index(index.row()-1, index.column(), index.parent());
        this->selectionModel()->select(id, QItemSelectionModel::ClearAndSelect);
    }else{
        QModelIndex id = this->imageModel->index(index.row(), index.column(), index.parent());
        this->selectionModel()->select(id, QItemSelectionModel::ClearAndSelect);
    }
}

void ImageListView::moveDown()
{
    QModelIndex index = this->getFirstSelectedItem();
    this->imageModel->moveUp(index);
    if (index.row() > 0) {
        QModelIndex id = this->imageModel->index(index.row()+1, index.column(), index.parent());
        this->selectionModel()->select(id, QItemSelectionModel::ClearAndSelect);
    }else{
        QModelIndex id = this->imageModel->index(index.row(), index.column(), index.parent());
        this->selectionModel()->select(id, QItemSelectionModel::ClearAndSelect);
    }
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
QModelIndex ImageListView::getFirstSelectedItem()
{
    QItemSelection s = this->selectionModel()->selection();
    if (!s.isEmpty())
        return s.first().indexes().first();
    return QModelIndex();
}
