#include "distortionwidget.h"
#include "distortionmodel.h"
#include "sciencedoubledelegate.h"
#include <QtWidgets>
DistortionWidget::DistortionWidget(QWidget *parent) : QWidget(parent)
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
    this->tableView->horizontalHeader()->setStretchLastSection(true);
    layout->addLayout(bLay);
    layout->addWidget(this->tableView);

    QGroupBox *groupBox = new QGroupBox(tr("Distortion Polynomial"));
    groupBox->setLayout(layout);
    QHBoxLayout *boxLayout = new QHBoxLayout;
    boxLayout->addWidget(groupBox);
    setLayout(boxLayout);
    connect(loadButton, SIGNAL(clicked(bool)), this, SLOT(loadFile()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveFile()));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clear()));
    this->tableView->setItemDelegate(new ScienceDoubleDelegate(this));
}

void DistortionWidget::setModel(DistortionModel *model)
{
    this->tableView->setModel(model);
    this->model = model;
}

QTableView *DistortionWidget::getView()
{
    return this->tableView;
}

void DistortionWidget::saveFile()
{
    QFileDialog dialog(this, tr("Save Distortion"), QDir::currentPath());
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    while (dialog.exec() == QDialog::Accepted)
        if (saveDistortion(dialog.selectedFiles())) break;
}

void DistortionWidget::loadFile()
{
    QFileDialog dialog(this, tr("Load Distortion"), QDir::currentPath());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    while (dialog.exec() == QDialog::Accepted)
        if (loadDistortion(dialog.selectedFiles())) break;
}

void DistortionWidget::clear()
{
    this->model->clear();
}

bool DistortionWidget::saveDistortion(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QSaveFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    DistortionValue value = this->model->core()->getValue();

    int size = value._size;

    // writing:
    st.setRealNumberPrecision(16);
    st<<"maxOrder: \n";
    st<<value._maxOrder<<'\n';
    st<<"Polynomial for X: \n";
    for (int i = 0; i < size; ++i)
        st<<value._XYData[i].first<<'\n';
    st<<"Polynomial for Y: \n";
    for (int i = 0; i < size; ++i)
        st<<value._XYData[i].second<<'\n';
    // end writing

    if (file.commit()) return true;
    else return false;
}

bool DistortionWidget::loadDistortion(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    DistortionValue value;
    int maxOrder, size;

    // reading
    st.setRealNumberPrecision(16);
    st.readLine();// "maxOrder: \n"
    st>>maxOrder;
    if (st.status() != QTextStream::Ok) return false;
    if (maxOrder < 0) return false;
    value.setMaxOrder(maxOrder);
    size = value._size;
    st.readLine();
    st.readLine();              // "\nPolynomial for X: \n"
    for (int i = 0; i < size; ++i)
        st>>value._XYData[i].first;
    st.readLine();
    st.readLine();              // "\nPolynomial for Y: \n"
    for (int i = 0; i < size; ++i)
        st>>value._XYData[i].second;
    if (st.status() != QTextStream::Ok) return false;
    // end reading
    this->model->core()->setValue(value);
    return true;
}
