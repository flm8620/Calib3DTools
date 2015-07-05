#include "point3dwidget.h"
#include "point3dmodel.h"
#include "sciencedoubledelegate.h"
#include <QtWidgets>
Point3DWidget::Point3DWidget(QWidget *parent) : QWidget(parent)
{
    this->view = new QTableView(this);
    this->view->setItemDelegate(new ScienceDoubleDelegate);
    QPushButton *addPointButton = new QPushButton(tr("+"));
    QPushButton *removePointButton = new QPushButton(tr("-"));
    QPushButton *moveUpButton = new QPushButton(tr("Up"));
    QPushButton *moveDownButton = new QPushButton(tr("Down"));
    QPushButton *loadButton = new QPushButton(tr("Load"));
    QPushButton *saveButton = new QPushButton(tr("Save"));
    QPushButton *clearButton = new QPushButton(tr("Clear"));
    addPointButton->setMaximumWidth(40);
    removePointButton->setMaximumWidth(40);
    moveUpButton->setMaximumWidth(40);
    moveDownButton->setMaximumWidth(40);

    QHBoxLayout *bLay1 = new QHBoxLayout;
    QHBoxLayout *bLay2 = new QHBoxLayout;
    bLay1->addWidget(addPointButton);
    bLay1->addWidget(removePointButton);
    bLay1->addWidget(moveUpButton);
    bLay1->addWidget(moveDownButton);
    bLay2->addWidget(loadButton);
    bLay2->addWidget(saveButton);
    bLay2->addWidget(clearButton);
    QVBoxLayout *bLay = new QVBoxLayout;
    bLay->addLayout(bLay1);
    bLay->addLayout(bLay2);

    connect(addPointButton, SIGNAL(clicked(bool)), this, SLOT(appendPoint()));
    connect(removePointButton, SIGNAL(clicked(bool)), this, SLOT(removePoint()));
    connect(loadButton, SIGNAL(clicked(bool)), this, SLOT(loadFile()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveFile()));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clear()));
    connect(moveUpButton, SIGNAL(clicked(bool)), this, SLOT(moveUp()));
    connect(moveDownButton, SIGNAL(clicked(bool)), this, SLOT(moveDown()));

    QVBoxLayout *hLay = new QVBoxLayout;
    hLay->addLayout(bLay);
    hLay->addWidget(view);

    QGroupBox *groupBox = new QGroupBox(tr("Point 3D"));
    groupBox->setLayout(hLay);
    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(groupBox);
    setLayout(lay);
}

void Point3DWidget::setModel(Point3DModel *model)
{
    this->model = model;
    view->setModel(model);
}

void Point3DWidget::appendPoint()
{
    this->model->append();
}

void Point3DWidget::removePoint()
{
    QModelIndex index = this->getFirstSelectedItem();
    model->removeRow(index.row());
    view->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
}

void Point3DWidget::moveUp()
{
    QModelIndex index = this->getFirstSelectedItem();
    this->model->moveUp(index);
    QModelIndex id = this->model->index(index.row()-1, index.column(), index.parent());
    this->view->selectionModel()->select(id, QItemSelectionModel::ClearAndSelect);
}

void Point3DWidget::moveDown()
{
    QModelIndex index = this->getFirstSelectedItem();
    this->model->moveDown(index);
    QModelIndex id = this->model->index(index.row()+1, index.column(), index.parent());
    this->view->selectionModel()->select(id, QItemSelectionModel::ClearAndSelect);
}

void Point3DWidget::saveFile()
{
    QFileDialog dialog(this, tr("Save Distortion"), QDir::currentPath());
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    while (dialog.exec() == QDialog::Accepted)
        if (savePoint3D(dialog.selectedFiles())) break;
}

void Point3DWidget::loadFile()
{
    QFileDialog dialog(this, tr("Load Distortion"), QDir::currentPath());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    while (dialog.exec() == QDialog::Accepted)
        if (loadPoint3D(dialog.selectedFiles())) break;
}

void Point3DWidget::clear()
{
    this->model->clear();
}

bool Point3DWidget::savePoint3D(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QSaveFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    QList<QVector3D> plist;
    this->model->core()->getContent(plist);

    int size = plist.size();

    // writing:
    st.setRealNumberPrecision(16);
    for (int i = 0; i < size; i++) {
        st<<tr("Point_%1\n").arg(i+1);
        st<<plist[i].x()<<'\t';
        st<<plist[i].y()<<'\t';
        st<<plist[i].z()<<'\n';
    }
    // end writing

    if (file.commit()) return true;
    else return false;
}

bool Point3DWidget::loadPoint3D(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    QList<QVector3D> plist;

    // reading
    st.setRealNumberPrecision(16);
    do {
        double x, y, z;
        st.readLine();// "Point_%1\n"
        st>>x>>y>>z;
        st.skipWhiteSpace();
        if (st.status() != QTextStream::Ok) return false;
        plist.append(QVector3D(x, y, z));
    } while (!st.atEnd());
    if (st.status() != QTextStream::Ok) return false;
    // end reading
    this->model->core()->setContent(plist);
    return true;
}

QModelIndex Point3DWidget::getFirstSelectedItem()
{
    QItemSelection s = view->selectionModel()->selection();
    if (!s.isEmpty())
        return s.first().indexes().first();
    return QModelIndex();
}
