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

    QCoreApplication::setOrganizationName("IMAGINE");
    QCoreApplication::setOrganizationDomain("imagine.com");
    QCoreApplication::setApplicationName("IMAGINE Stereovision Tool");

    QSettings qsettings;
    qRegisterMetaType<libMsg::MessageType>();

    MainWindow w;
    libMsg::globalMessager = &w;
    w.show();

    return a.exec();
}
