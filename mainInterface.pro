#-------------------------------------------------
#
# Project created by QtCreator 2015-05-26T10:48:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mainInterface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    solver.cpp \
    imagelistmodel.cpp \
    imagelistview.cpp \
    imageviewer.cpp \
    imagelistwidget.cpp \
    distortionmodel.cpp \
    kmatrixmodel.cpp \
    point2dmodel.cpp \
    point2dview.cpp \
    point2dwidget.cpp \
    point3dwidget.cpp \
    point3dmodel.cpp \
    ClickImage/controllertableview.cpp \
    ClickImage/marker.cpp \
    ClickImage/markerimageview.cpp \
    ClickImage/myscene.cpp \
    ClickImage/mytest.cpp \
    ClickImage/clickdialog.cpp \
    console.cpp

HEADERS  += mainwindow.h \
    solver.h \
    imagelistmodel.h \
    imagelistview.h \
    imageviewer.h \
    imagelistwidget.h \
    distortionmodel.h \
    kmatrixmodel.h \
    point2dmodel.h \
    point2dview.h \
    point2dwidget.h \
    point3dwidget.h \
    point3dmodel.h \
    ClickImage/controllertableview.h \
    ClickImage/marker.h \
    ClickImage/markerimageview.h \
    ClickImage/myscene.h \
    ClickImage/mytest.h \
    ClickImage/clickdialog.h \
    console.h
