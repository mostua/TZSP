#include "view/mainwindow.h"
#include "controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Controller controller;

    QObject::connect(&controller, SIGNAL(simulationStarted()), &w, SIGNAL(activateButtons()));
    QObject::connect(&w, SIGNAL(startSimulation(Settings)), &controller, SLOT(beginSimulation(Settings)));
    w.show();
    return a.exec();
}

