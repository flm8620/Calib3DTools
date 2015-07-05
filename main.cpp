#include <QApplication>
#include <QList>
#include <QImage>
#include "mainwindow.h"
#include "distortion.h"
#include "imagelist.h"
#include "point3d.h"
#include "kmatrix.h"

Q_DECLARE_METATYPE(libMsg::MessageType)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    qRegisterMetaType<QVector<int>>(); // The QT complained the type not registered when the KmatrixModel emits the dataChanged signal.
//    qRegisterMetaType<KMatrix>("KMatrix");
//    qRegisterMetaType<Distortion>("Distortion");
//    qRegisterMetaType<ImageList >("ImageList");
//    qRegisterMetaType<Target2D>();
//    qRegisterMetaType<Target3D>("Target3D");

    qRegisterMetaType<libMsg::MessageType>();

    MainWindow w;
    libMsg::globalMessager = &w;
    w.show();

    return a.exec();
}
