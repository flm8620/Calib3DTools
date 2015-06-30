#include "kmatrixwidget.h"

KMatrixWidget::KMatrixWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *loadButton = new QPushButton(tr("Load"));
    QPushButton *saveButton = new QPushButton(tr("Save"));
    QPushButton *clearButton = new QPushButton(tr("Clear"));
    QHBoxLayout *bLay = new QHBoxLayout;
    bLay->addWidget(loadButton);
    bLay->addWidget(saveButton);
    bLay->addWidget(clearButton);
    this->view = new QTableView;
    layout->addLayout(bLay);
    layout->addWidget(this->view);

    QGroupBox *groupBox = new QGroupBox(tr("KMatrix"));
    groupBox->setLayout(layout);
    QHBoxLayout *boxLayout = new QHBoxLayout;
    boxLayout->addWidget(groupBox);
    setLayout(boxLayout);
    connect(loadButton, SIGNAL(clicked(bool)), this, SLOT(loadFile()));
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveFile()));
    connect(clearButton, SIGNAL(clicked(bool)), this, SLOT(clear()));
}

void KMatrixWidget::setModel(KMatrixModel *model)
{
    this->model = model;
    this->view->setModel(model);
}

QTableView *KMatrixWidget::getView()
{
    return this->view;
}

void KMatrixWidget::saveFile()
{
    QFileDialog dialog(this, tr("Save Matrix K"), QDir::currentPath());
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    while (dialog.exec() == QDialog::Accepted)
        if (saveKMatrix(dialog.selectedFiles())) break;
}

void KMatrixWidget::loadFile()
{
    QFileDialog dialog(this, tr("Load Distortion"), QDir::currentPath());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    while (dialog.exec() == QDialog::Accepted)
        if (loadKMatrix(dialog.selectedFiles())) break;
}

void KMatrixWidget::clear()
{
    this->model->clear();
}

bool KMatrixWidget::saveKMatrix(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QSaveFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    KValue value = this->model->core().getValue();


    // writing:
    st.setRealNumberPrecision(16);
    st<<"fx: \n";
    st<<value.fx<<'\n';
    st<<"fy: \n";
    st<<value.fy<<'\n';
    st<<"x0: \n";
    st<<value.x0<<'\n';
    st<<"y0: \n";
    st<<value.y0<<'\n';
    st<<"s: \n";
    st<<value.s<<'\n';


    if (file.commit()) return true;
    else return false;
}

bool KMatrixWidget::loadKMatrix(const QStringList &list)
{
    if (list.size() != 1) return false;
    QString name = list.first();
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream st(&file);
    KValue value;

    // reading
    st.setRealNumberPrecision(16);
    st.readLine();// "fx: \n"
    st>>value.fx;
    st.readLine();//n"
    st.readLine();// "fy: \n"
    st>>value.fy;
    st.readLine();//n"
    st.readLine();// "x0: \n"
    st>>value.x0;
    st.readLine();//n"
    st.readLine();// "y0: \n"
    st>>value.y0;
    st.readLine();//n"
    st.readLine();// "s: \n"
    st>>value.s;

    if (st.status() != QTextStream::Ok) return false;
    // end reading
    this->model->core().setValue(value);
    return true;
}
