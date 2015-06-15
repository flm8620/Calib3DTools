#include "imagelistview.h"
#include "imageviewer.h"
#include <QMessageBox>
#include <QImage>
#include <QFileInfo>
#include <QFileDialog>

ImageListView::ImageListView(QWidget *parent)
    :QListView(parent)
{

}

void ImageListView::openImage()
{
    QFileDialog dialog(this,tr("Open Image"),QDir::currentPath());
    //QStringList formatList;
    QStringList filters;
    filters << "Image files (*.png *.bmp *.jpg *.jpeg)"
            << "Any files (*)";

    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    //dialog.setMimeTypeFilters(formatList);
    dialog.setNameFilters(filters);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    while(dialog.exec() == QDialog::Accepted){
        if(loadImage(dialog.selectedFiles())) break;
    }
}

bool ImageListView::loadImage(const QStringList& list)
{
    QString filePath;
    foreach(filePath,list){
        QImage image(filePath);
        if(image.isNull()){
            QMessageBox::information(this,"Error",tr("Cannot load %1").arg(filePath));
            return false;
        }
    }
    foreach (filePath, list) {
        QFileInfo info(filePath);
        QString name=info.fileName();
        QImage image(filePath);
        Q_ASSERT(!image.isNull());
        addImage(name,image);
    }
    return true;
}

void ImageListView::addImage(const QString &string, QImage image)
{
    Q_ASSERT(!image.isNull());
    QAbstractItemModel* m=model();
    int row=m->rowCount();
    m->insertRow(row);
    QModelIndex id=m->index(row,0);
    m->setData(id,string,Qt::DisplayRole);
    m->setData(id,image,Qt::UserRole);
}

void ImageListView::deleteImage()
{
    QModelIndexList idList=selectionModel()->selectedRows();
    if(idList.isEmpty())return;
    int row=idList.first().row();
    QAbstractItemModel* m=model();
    m->removeRow(row);
}

void ImageListView::moveUp()
{
    QModelIndexList idList=selectionModel()->selectedRows();
    if(idList.isEmpty())return;
    int row=idList.first().row();
    QAbstractItemModel* m=model();
    if(row<=0||row>=m->rowCount())return;
    QModelIndex id=m->index(row,0);
    QString name=qvariant_cast<QString>(m->data(id,Qt::DisplayRole));
    QImage image=qvariant_cast<QImage>(m->data(id,Qt::UserRole));
    m->removeRow(row);
    m->insertRow(row-1);
    id=m->index(row-1,0);
    m->setData(id,name,Qt::DisplayRole);
    m->setData(id,image,Qt::UserRole);
    selectionModel()->select(id,QItemSelectionModel::ClearAndSelect);
}

void ImageListView::moveDown()
{
    QModelIndexList idList=selectionModel()->selectedRows();
    if(idList.isEmpty())return;
    int row=idList.first().row();
    QAbstractItemModel* m=model();
    if(row<0||row>=m->rowCount()-1)return;
    QModelIndex id=m->index(row,0);
    QString name=qvariant_cast<QString>(m->data(id,Qt::DisplayRole));
    QImage image=qvariant_cast<QImage>(m->data(id,Qt::UserRole));
    m->removeRow(row);
    m->insertRow(row+1);
    id=m->index(row+1,0);
    m->setData(id,name,Qt::DisplayRole);
    m->setData(id,image,Qt::UserRole);
    selectionModel()->select(id,QItemSelectionModel::ClearAndSelect);
}

void ImageListView::openInViewer()
{
    QModelIndexList idList=selectionModel()->selectedRows();
    if(idList.isEmpty())return;
    int row=idList.first().row();
    QAbstractItemModel* m=model();
    QModelIndex id=m->index(row,0);
    QImage image=qvariant_cast<QImage>(m->data(id,Qt::UserRole));
    Q_ASSERT(!image.isNull());
    ImageViewer* viewer=new ImageViewer(image,this);
    viewer->setWindowFlags(Qt::Window);
    viewer->show();

}
