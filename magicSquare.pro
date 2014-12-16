#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T12:46:02
#
#-------------------------------------------------

QT       += core gui printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = magicSquare
TEMPLATE = app


SOURCES += main.cpp\
        view/mainwindow.cpp \
    model/testMutation.cpp \
    model/mainModel.cpp \
    model/model.cpp \
    controller/controller.cpp \
    qcustomplot-source/qcustomplot.cpp

HEADERS  += view/mainwindow.h \
    model/fitness.h \
    model/mutation.h \
    model/population.h \
    model/reproduction.h \
    model/square.h \
    model/model.h \
    controller/controller.h \
    qcustomplot-source/qcustomplot.h

FORMS    += view/mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11