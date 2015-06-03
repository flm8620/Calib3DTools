#include "mainwindow.h"
#include <QApplication>
#include <QList>
#include <QImage>
#include "solver.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<Distortion>();
    qRegisterMetaType<QList<QImage> >();
    qRegisterMetaType<Target2D>();
    qRegisterMetaType<Target3D>();
    qRegisterMetaType<KMatrix>();
    MainWindow w;
    w.show();

    return a.exec();
}
