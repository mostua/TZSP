#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T12:46:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MagicSquereView
TEMPLATE = app


SOURCES += main.cpp\
        view/mainwindow.cpp \
    model/testMutation.cpp \
    model/mainModel.cpp

HEADERS  += view/mainwindow.h \
    model/fitness.h \
    model/mutation.h \
    model/population.h \
    model/reproduction.h \
    model/square.h

FORMS    += view/mainwindow.ui
