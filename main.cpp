#include "view/mainwindow.h"
#include "controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Controller controller;

    QObject::connect(&controller, SIGNAL(stepSimulationStarted()), &w, SIGNAL(activateStepButtons()));
    QObject::connect(&controller, SIGNAL(continousSimulationStarted()), &w, SIGNAL(activateContinousButtons()));
    QObject::connect(&w, SIGNAL(startStepSimulation(Settings)), &controller, SLOT(beginStepSimulation(Settings)));
    QObject::connect(&w, SIGNAL(startContinousSimulation(Settings)), &controller, SLOT(beginContinousSimulation(Settings)));
    w.show();
    return a.exec();
}

