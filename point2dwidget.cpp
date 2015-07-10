#include "point2dwidget.h"
#include "point2dview.h"
#include "point2dmodel.h"
#include "sciencedoubledelegate.h"
#include <QtWidgets>
Point2DWidget::Point2DWidget(QWidget *parent) : QWidget(parent)
{
    view = new Point2DView(this);
    ScienceDoubleDelegate *delegate = new ScienceDoubleDelegate(this);
    delegate->setPrecision(6);
    this->view->setItemDelegate(delegate);
    QPushButton *addPointButton = new QPushButton(tr("+"));
    QPushButton *removePointButton = new QPushButton(tr("-"));
    QPushButton *moveUpButton = new QPushButton(tr("^"));
    QPushButton *moveDownButton = new QPushButton(tr("v"));
    QPushButton *loadButton = new QPushButton(tr("Load"));
    QPushButton *saveButton = new QPushButton(tr("Save"));
    QPushButton *clearButton = new QPushButton(tr("Clear"));

    addPointButton->setMaximumWidth(20);
    removePointButton->setMaximumWidth(20);
    moveUpButton->setMaximumWidth(20);
    moveDownButton->setMaximumWidth(20);
    loadButton->setMaximumWidth(40);
    saveButton->setMaximumWidth(40);
    clearButton->setMaximumWidth(40);

    addPointButton->setMaximumHeight(20);
    removePointButton->setMaximumHeight(20);
    moveUpButton->setMaximumHeight(20);
    moveDownButton->setMaximumHeight(20);
    loadButton->setMaximumHeight(20);
    saveButton->setMaximumHeight(20);
    clearButton->setMaximumHeight(20);

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

    connect(addPointButton, SIGNAL(clicked(bool)), this, SLOT(addPoint()));
    connect(removePointButton, SIGNAL(clicked(bool)), this, SLOT(removePoint()));
    connect(loadButton, SIGNAL(clicked(bool)), this, SLOT(loadFile()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveFile()));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clear()));
    connect(moveUpButton, SIGNAL(clicked(bool)), this, SLOT(movePointUp()));
    connect(moveDownButton, SIGNAL(clicked(bool)), this, SLOT(movePointDown()));

    QVBoxLayout *hLay = new QVBoxLayout;
    hLay->addLayout(bLay);
    hLay->addWidget(view);

    QGroupBox *groupBox = new QGroupBox(tr("Point 2D"));
    groupBox->setLayout(hLay);
    QHBoxLayout *lay = new QHBoxLayout;
    lay->addWidget(groupBox);
    setLayout(lay);
}

void Point2DWidget::setModel(Point2DModel *model)
{
    this->model = model;
    view->setPoint2DModel(model);
}

Point2DView *Point2DWidget::getPoint2DView()
{
    return this->view;
}

void Point2DWidget::addPoint()
{
    this->model->appendPoint();
}

void Point2DWidget::removePoint()
{
    QModelIndex sId = this->getFirstSelectedItem();
    this->model->removePoint(sId);
}

void Point2DWidget::movePointUp()
{
    QModelIndex index = this->getFirstSelectedItem();
    if (this->model->indexMeansPoint(index)) {
        this->model->movePointUp(index);
        if (index.row() > 0) {
            QModelIndex id = this->model->index(index.row()-1, index.column(), index.parent());
            this->view->selectionModel()->select(id,
                                                 QItemSelectionModel::ClearAndSelect
                                                 |QItemSelectionModel::Rows);
        } else {
            QModelIndex id = this->model->index(index.row(), index.column(), index.parent());
            this->view->selectionModel()->select(id,
                                                 QItemSelectionModel::ClearAndSelect
                                                 |QItemSelectionModel::Rows);
        }
    }
}

void Point2DWidget::movePointDown()
{
    QModelIndex index = this->getFirstSelectedItem();
    if (this->model->indexMeansPoint(index)) {
        this->model->movePointDown(index);
        if (index.row() < this->model->pointCount()-1) {
            QModelIndex id = this->model->index(index.row()+1, index.column(), index.parent());
            this->view->selectionModel()->select(id,
                                                 QItemSelectionModel::ClearAndSelect
                                                 |QItemSelectionModel::Rows);
        } else {
            QModelIndex id = this->model->index(index.row(), index.column(), index.parent());
            this->view->selectionModel()->select(id,
                                                 QItemSelectionModel::ClearAndSelect
                                                 |QItemSelectionModel::Rows);
        }
    }
}

void Point2DWidget::saveFile()
{
    QSettings settings;
    QFileDialog dialog(this, tr("Save Distortion"), settings.value("default_dir").toString());
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    while (dialog.exec() == QDialog::Accepted)
        if (savePoint2D(dialog.selectedFiles())) break;
    if (!dialog.selectedFiles().isEmpty())
        settings.setValue("default_dir", dialog.selectedFiles().first());
}

void Point2DWidget::loadFile()
{
    QSettings settings;
    QFileDialog dialog(this, tr("Load Distortion"), settings.value("default_dir").toString());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    while (dialog.exec() == QDialog::Accepted)
        if (loadPoint2D(dialog.selectedFiles())) break;
    if (!dialog.selectedFiles().isEmpty())
        settings.setValue("default_dir", dialog.selectedFiles().first());
}

void Point2DWidget::clear()
{
    this->model->clear();
}

bool Point2DWidget::savePoint2D(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QSaveFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    QList<QList<QPointF> > plist;
    this->model->core()->getAllPoints(plist);

    int size = plist.size();
    if (size == 0) return false;
    int pointcount = plist[0].size();

    // writing:
    st.setRealNumberPrecision(16);
    st<<"ImageCount:\n"<<size<<'\n';
    st<<"PointCount:\n"<<pointcount<<'\n';
    for (int i = 0; i < size; i++) {
        st<<tr("Image_%1").arg(i+1)<<'\n';
        for (int j = 0; j < pointcount; ++j) {
            st<<plist[i][j].x()<<'\t';
            st<<plist[i][j].y()<<'\n';
        }
    }
    // end writing

    if (file.commit()) return true;
    else return false;
}

bool Point2DWidget::loadPoint2D(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    QList<QList<QPointF> > plist;
    int size, pointcount;
    // reading
    st.setRealNumberPrecision(16);
    st.readLine();// ImageCount
    st>>size;
    st.skipWhiteSpace();
    st.readLine();// PointCount
    st>>pointcount;
    st.skipWhiteSpace();
    if (st.status() != QTextStream::Ok) return false;
    for (int i = 0; i < size; i++) {
        plist.append(QList<QPointF>());
        st.readLine();// Image_i
        for (int j = 0; j < pointcount; ++j) {
            double x, y;
            st>>x>>y;
            st.skipWhiteSpace();
            plist[i].append(QPointF(x, y));
        }
    }
    if (st.status() != QTextStream::Ok) return false;
    // end reading
    this->model->core()->setAllPoints(plist);
    return true;
}

QModelIndex Point2DWidget::getFirstSelectedItem()
{
    QItemSelection s = view->selectionModel()->selection();
    if (!s.isEmpty())
        return s.first().indexes().first();
    return QModelIndex();
}
