#include <QApplication>
#include <QList>
#include <QImage>
#include "mainwindow.h"
#include "distortion.h"
#include "imagelist.h"
#include "target2d.h"
#include "target3d.h"
#include "kmatrix.h"
Q_DECLARE_METATYPE(libMsg::MessageType);
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qRegisterMetaType<Distortion>();
    //qRegisterMetaType<ImageList >("ImageList");
    qRegisterMetaType<Target2D>();
    qRegisterMetaType<Target3D>("Target3D");

    qRegisterMetaType<libMsg::MessageType>();
    //qRegisterMetaType<KMatrix>();

    MainWindow w;
    libMsg::globalMessager=&w;
    w.show();

    return a.exec();
}
