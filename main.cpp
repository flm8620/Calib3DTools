#include <QApplication>
#include <QList>
#include <QImage>
#include "mainwindow.h"
#include "distortion.h"
#include "imagelist.h"
#include "point3d.h"
#include "kmatrix.h"
Q_DECLARE_METATYPE(libMsg::MessageType);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // qRegisterMetaType<Distortion>();
    // qRegisterMetaType<ImageList >("ImageList");
// qRegisterMetaType<Target2D>();
// qRegisterMetaType<Point3D>("Point3D");

    qRegisterMetaType<libMsg::MessageType>();
    // qRegisterMetaType<KMatrix>();

    MainWindow w;
    libMsg::globalMessager = &w;
    w.show();

    return a.exec();
}
