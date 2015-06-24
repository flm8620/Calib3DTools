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
    qRegisterMetaType<QVector<int>>(); // The QT complained the type not registered when the KmatrixModel emits the dataChanged signal.
    qRegisterMetaType<KMatrix>("KMatrix");
    qRegisterMetaType<Distortion>("Distortion");
    qRegisterMetaType<ImageList >("ImageList");
    qRegisterMetaType<Target2D>();
    qRegisterMetaType<Target3D>("Target3D");

    MainWindow w;
    w.show();

    return a.exec();
}
