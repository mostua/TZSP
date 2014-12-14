#include "view/mainwindow.h"
#include "controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Controller controller;

    QObject::connect(&controller, SIGNAL(returnIteration(QString)), &w, SLOT(addIteration(QString)));
    QObject::connect(&w, SIGNAL(startSimulation(unsigned int)), &controller, SLOT(beginSimulation(unsigned int)));
    w.show();

    return a.exec();
}

