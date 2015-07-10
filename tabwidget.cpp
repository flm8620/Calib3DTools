#include "tabwidget.h"
// #include "imagelistmodel.h"
#include "point2dwidget.h"
#include "point3dwidget.h"
#include "rapidjson/document.h"
DistortionTab::DistortionTab(QWidget *parent) : QWidget(parent)
{
    this->harpPhotoWidget = new ImageListWidget(tr("Harp Photo"));
    this->harpFeedbackWidget = new ImageListWidget(tr("Detect Feedback"));
    this->calculateButton = new QPushButton(tr("Calculate Distortion Polynomial"));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->harpPhotoWidget);
    lay->addWidget(this->calculateButton);
    lay->addWidget(this->harpFeedbackWidget);
    this->setLayout(lay);
}

void DistortionTab::connectToSolver(Solver *solver)
{
    connect(this->calculateButton, SIGNAL(clicked(bool)), solver, SLOT(onCalculateDistortion()));
}

void DistortionTab::registerModel(ImageListModel *harpPhotoModel, ImageListModel *harpFeedbackModel)
{
    this->harpPhotoWidget->setModel(harpPhotoModel);
    this->harpFeedbackWidget->setModel(harpFeedbackModel);
}

void DistortionTab::connectToImageViewer(ImageViewer *viewer)
{
    ImageListView *view = this->harpPhotoWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
    view = this->harpFeedbackWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
}

KMatrixTab::KMatrixTab(QWidget *parent) : QWidget(parent)
{
    this->circlePhotoWidget = new ImageListWidget(tr("Circle Photo"));
    this->circleCorrectedWidget = new ImageListWidget(tr("Corrected Circle Photo"));
    this->circleFeedbackWidget = new ImageListWidget(tr("Detect Feedback"));
    this->calculateButton = new QPushButton(tr("Calculate Matrix K"));
    this->correctDistButton = new QPushButton(tr("Apply Distortion Correction"));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->circlePhotoWidget);
    lay->addWidget(this->correctDistButton);
    lay->addWidget(this->circleCorrectedWidget);
    lay->addWidget(this->calculateButton);
    lay->addWidget(this->circleFeedbackWidget);
    this->setLayout(lay);
}

void KMatrixTab::connectToSolver(Solver *solver)
{
    connect(this->correctDistButton, SIGNAL(clicked(bool)), solver,
            SLOT(onCorrectCircle()));
    connect(this->calculateButton, SIGNAL(clicked(bool)), solver, SLOT(onCalculateK()));
}

void KMatrixTab::registerModel(ImageListModel *circlePhotoModel,
                               ImageListModel *circleCorrectedModel,
                               ImageListModel *circleFeedbackModel)
{
    this->circlePhotoWidget->setModel(circlePhotoModel);
    this->circleCorrectedWidget->setModel(circleCorrectedModel);
    this->circleFeedbackWidget->setModel(circleFeedbackModel);
}

void KMatrixTab::connectToImageViewer(ImageViewer *viewer)
{
    ImageListView *view = this->circlePhotoWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
    view = this->circleCorrectedWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
    view = this->circleFeedbackWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
}

PhotoTab::PhotoTab(QWidget *parent) : QWidget(parent)
{
    this->photoWidget = new ImageListWidget(tr("Photo"));
    this->correctedWidget = new ImageListWidget(tr("Corrected Photo"));
    this->correctDistButton = new QPushButton(tr("Apply Distortion Correction"));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->photoWidget);
    lay->addWidget(this->correctDistButton);
    lay->addWidget(this->correctedWidget);
    this->setLayout(lay);
}

void PhotoTab::connectToSolver(Solver *solver)
{
    connect(this->correctDistButton, SIGNAL(clicked(bool)), solver, SLOT(onCorrectPhoto()));
}

void PhotoTab::registerModel(ImageListModel *photoModel, ImageListModel *correctedModel)
{
    this->photoWidget->setModel(photoModel);
    this->correctedWidget->setModel(correctedModel);
}

void PhotoTab::connectToImageViewer(ImageViewer *viewer)
{
    ImageListView *view = this->photoWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
    view = this->correctedWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
}

Point2DTab::Point2DTab(QWidget *parent) : QWidget(parent)
{
    this->correctedWidget = new ImageListWidget(tr("Corrected Photo"));
    this->point2DWidget = new Point2DWidget;

    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->correctedWidget);
    lay->addWidget(this->point2DWidget);
    this->setLayout(lay);
}

void Point2DTab::registerModel(ImageListModel *correctedModel, Point2DModel *point2DModel)
{
    this->correctedWidget->setModel(correctedModel);
    this->point2DWidget->setModel(point2DModel);
}

void Point2DTab::connectToImageViewer(ImageViewer *viewer)
{
    ImageListView *view = this->correctedWidget->getView();
    connect(view, SIGNAL(imageToDisplay(QImage)), viewer, SLOT(setImage(QImage)));
}

void Point2DTab::connectToMarkerViewer(MarkerImageView *markerViewer)
{
    markerViewer->setPoint2DView(this->point2DWidget->getPoint2DView());
}

Point3DTab::Point3DTab(QWidget *parent)
{
    this->point3DWidget = new Point3DWidget;
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->point3DWidget);
    this->setLayout(lay);
}

void Point3DTab::registerModel(Point3DModel *point3DModel)
{
    this->point3DWidget->setModel(point3DModel);
}

CamPosTab::CamPosTab(QWidget *parent) : QWidget(parent)
{
    this->camPosWidget = new CamPosWidget;
    this->solveStrecha = new QPushButton(tr("Solve by Strecha's' Method"));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->camPosWidget);
    lay->addWidget(this->solveStrecha);
    this->setLayout(lay);
}

void CamPosTab::connectToSolver(Solver *solver)
{
    connect(this->solveStrecha, SIGNAL(clicked(bool)), solver, SLOT(onSolveStrecha()));
}

void CamPosTab::registerModel(CamPosModel *camPosModel)
{
    this->camPosWidget->setModel(camPosModel);
}

CamCompareTab::CamCompareTab(QWidget *parent)
{
    this->camPosWidget = new CamPosWidget;
    this->loadFromOpenMVGjson = new QPushButton(tr("loadFromOpenMVG *.json "));
    this->compareButton = new QPushButton(tr("Compare with CamPos"));
    QVBoxLayout *lay = new QVBoxLayout;
    lay->addWidget(this->camPosWidget);
    lay->addWidget(this->loadFromOpenMVGjson);
    lay->addWidget(this->compareButton);
    this->setLayout(lay);

    connect(this->loadFromOpenMVGjson, SIGNAL(clicked(bool)), this, SLOT(loadJson()));
}

void CamCompareTab::connectToSolver(Solver *solver)
{
    connect(this->compareButton,SIGNAL(clicked(bool)),solver,SLOT(onCompareCam()));
}

void CamCompareTab::registerModel(CamPosModel *camPosModel)
{
    this->camPosWidget->setModel(camPosModel);
}

void CamCompareTab::loadJson()
{
    QSettings settings;
    QFileDialog dialog(this, tr("Load json"), settings.value("default_dir").toString());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    while (dialog.exec() == QDialog::Accepted)
        if (loadCamPos(dialog.selectedFiles())) break;
    if (!dialog.selectedFiles().isEmpty())
        settings.setValue("default_dir", dialog.selectedFiles().first());
}

bool CamCompareTab::loadCamPos(const QStringList &list)
{
    QString qs;
    {
        if (list.size() != 1) return false;
        QString name = list.first();
        QFile file(name);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return false;
        QTextStream st(&file);
        qs = st.readAll().toLatin1();
    }

    QByteArray ba = qs.toLatin1();
    const char *c_str = ba.data();

    CameraPosValue cameraValue;

    using namespace rapidjson;
    Document Doc;
    Doc.Parse(c_str);
    if (!Doc.HasMember("extrinsics")) return false;
    const Value &ex = Doc["extrinsics"];
    if (!ex.IsArray()) return false;
    if (ex.Size() <= 0) return false;
    for (int i = 0; i < ex.Size(); i++) {
        const Value &item = ex[i];
        if (!item.HasMember("value")) return false;
        const Value &value = item["value"];
        if (!value.HasMember("center")) return false;
        const Value &center = value["center"];
        if (!center.IsArray()) return false;
        if (center.Size() != 3) return false;

        std::vector<double> R, C;

        for (int j = 0; j < 3; j++) {
            if (!center[j].IsDouble()) return false;
            C.push_back(center[j].GetDouble());
        }

        if (!value.HasMember("rotation")) return false;
        const Value &rotation = value["rotation"];
        if (!rotation.IsArray()) return false;
        if (rotation.Size() != 3) return false;
        for (int j = 0; j < 3; j++) {
            const Value &row = rotation[j];
            if (!row.IsArray()) return false;
            if (row.Size() != 3) return false;
            for (int k = 0; k < 3; k++) {
                if (!row[k].IsDouble()) return false;
                R.push_back(row[k].GetDouble());
            }
        }
        cameraValue.data.append(qMakePair(R,C));
    }
    this->camPosWidget->getModel()->core()->setValue(cameraValue);
}

TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
{
    this->distortionTab = new DistortionTab;
    this->kmatrixTab = new KMatrixTab;
    this->photoTab = new PhotoTab;
    this->point2dTab = new Point2DTab;
    this->point3dTab = new Point3DTab;
    this->camPosTab = new CamPosTab;
    this->camCompareTab=new CamCompareTab;

    this->addTab(distortionTab, tr("Distortion"));
    this->addTab(kmatrixTab, tr("KMatrix"));
    this->addTab(photoTab, tr("Photo"));
    this->addTab(point2dTab, tr("Point2D"));
    this->addTab(point3dTab, tr("Point3D"));
    this->addTab(camPosTab, tr("Camera"));
    this->addTab(camCompareTab, tr("CamCompare"));
    this->setTabPosition(QTabWidget::East);
}

void TabWidget::connectToSolver(Solver *solver)
{
    this->distortionTab->connectToSolver(solver);
    this->kmatrixTab->connectToSolver(solver);
    this->photoTab->connectToSolver(solver);
    this->camPosTab->connectToSolver(solver);
    this->camCompareTab->connectToSolver(solver);
}

void TabWidget::registerModel(ImageListModel *harpPhotoModel, ImageListModel *harpFeedbackModel,
                              ImageListModel *circlePhotoModel,
                              ImageListModel *circleCorrectedModel,
                              ImageListModel *circleFeedbackModel, ImageListModel *photoModel,
                              ImageListModel *photoCorrectedModel, Point2DModel *point2DModel,
                              Point3DModel *point3DModel, CamPosModel *camPosModel,CamPosModel *camCompareModel)
{
    this->distortionTab->registerModel(harpPhotoModel, harpFeedbackModel);
    this->kmatrixTab->registerModel(circlePhotoModel, circleCorrectedModel, circleFeedbackModel);
    this->photoTab->registerModel(photoModel, photoCorrectedModel);
    this->point2dTab->registerModel(photoCorrectedModel, point2DModel);
    this->point3dTab->registerModel(point3DModel);
    this->camPosTab->registerModel(camPosModel);
    this->camCompareTab->registerModel(camCompareModel);
}

void TabWidget::connectToImageViewer(ImageViewer *viewer)
{
    this->distortionTab->connectToImageViewer(viewer);
    this->kmatrixTab->connectToImageViewer(viewer);
    this->photoTab->connectToImageViewer(viewer);
    this->point2dTab->connectToImageViewer(viewer);
}

void TabWidget::connectToMarkerViewer(MarkerImageView *markerViewer)
{
    this->point2dTab->connectToMarkerViewer(markerViewer);
}
