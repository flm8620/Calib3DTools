#include "camposwidget.h"
#include "camposmodel.h"
#include "sciencedoubledelegate.h"
#include <QtWidgets>
#include <QDebug>
CamPosWidget::CamPosWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *loadButton = new QPushButton(tr("Load"));
    QPushButton *saveButton = new QPushButton(tr("Save"));
    QPushButton *clearButton = new QPushButton(tr("Clear"));
    QHBoxLayout *bLay = new QHBoxLayout;
    bLay->addWidget(loadButton);
    bLay->addWidget(saveButton);
    bLay->addWidget(clearButton);
    this->tableView = new QTableView;

    layout->addLayout(bLay);
    layout->addWidget(this->tableView);

    QGroupBox *groupBox = new QGroupBox(tr("CamPos"));
    groupBox->setLayout(layout);
    QHBoxLayout *boxLayout = new QHBoxLayout;
    boxLayout->addWidget(groupBox);
    setLayout(boxLayout);
    connect(loadButton, SIGNAL(clicked(bool)), this, SLOT(loadFile()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveFile()));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clear()));
    this->tableView->setItemDelegate(new ScienceDoubleDelegate);
}

void CamPosWidget::setModel(CamPosModel *model)
{
    this->tableView->setModel(model);
    this->model = model;
}

QTableView *CamPosWidget::getView()
{
    return this->tableView;
}

void CamPosWidget::saveFile()
{
    QFileDialog dialog(this, tr("Save Distortion"), QDir::currentPath());
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    while (dialog.exec() == QDialog::Accepted)
        if (saveCamPos(dialog.selectedFiles())) break;
}

void CamPosWidget::loadFile()
{
    QFileDialog dialog(this, tr("Load Distortion"), QDir::currentPath());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    while (dialog.exec() == QDialog::Accepted)
        if (loadCamPos(dialog.selectedFiles())) break;
}

void CamPosWidget::clear()
{
    this->model->clear();
}

bool CamPosWidget::saveCamPos(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QSaveFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    CameraPosValue value = this->model->core()->getValue();

    int size = value.data.size();

    // writing:
    st.setRealNumberPrecision(16);
    for (int i = 0; i < size; i++) {
        st<<tr("Camera %1\n").arg(i+1);
        st<<"Matrix R:\n";
        for (int j = 0; j < 3; ++j) {
            st<<value.data[i].first[j*3+0]<<'\t';
            st<<value.data[i].first[j*3+1]<<'\t';
            st<<value.data[i].first[j*3+2]<<'\n';
        }
        st<<"Center:\n";
        st<<value.data[i].second[0]<<'\t'
          <<value.data[i].second[1]<<'\t'
          <<value.data[i].second[2]<<'\n';
        st<<'\n';
    }
    // end writing

    if (file.commit()) return true;
    else return false;
}

bool CamPosWidget::loadCamPos(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    CameraPosValue value;

    // reading
    st.setRealNumberPrecision(16);
    do {
        st.readLine();// "Camera %1\n"
        st.readLine();// "Matrix R\n"
        std::vector<double> R, C;
        for (int j = 0; j < 9; ++j) {
            double val;
            st>>val;
            qDebug()<<val;
            R.push_back(val);
        }
        st.skipWhiteSpace();
        st.readLine();// "Cam Center \n"
        for (int j = 0; j < 3; ++j) {
            double val;
            st>>val;
            qDebug()<<val;
            C.push_back(val);
        }
        st.skipWhiteSpace();
        if (st.status() != QTextStream::Ok) return false;
        value.data.push_back(qMakePair(R, C));
    } while (!st.atEnd());
    if (st.status() != QTextStream::Ok) return false;
    // end reading
    this->model->core()->setValue(value);
    return true;
}
