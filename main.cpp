#include <QApplication>
#include <QList>
#include <QImage>
#include "mainwindow.h"
#include "distortion.h"
#include "imagelist.h"
#include "target2d.h"
#include "target3d.h"
#include "kmatrix.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Distortion>("Distortion");
    qRegisterMetaType<ImageList >("ImagList");
    qRegisterMetaType<Target2D>();
    qRegisterMetaType<Target3D>("Target3D");
    qRegisterMetaType<KMatrix>();

    MainWindow w;
    w.show();

    return a.exec();
}
