#include "model/model.h"
#include "view/mainwindow.h"
#include "controller/controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    MainWindow view(&model);
    Controller controller(&model);
    qRegisterMetaType<vectorSquares>("vectorSquares");
    QObject::connect(&controller, SIGNAL(stepSimulationStarted()), &view, SIGNAL(activateStepButtons()));
    QObject::connect(&controller, SIGNAL(continousSimulationStarted()), &view, SIGNAL(activateContinousButtons()));
    QObject::connect(&controller, SIGNAL(simulationReseted()), &view, SIGNAL(simulationReseted()));
    QObject::connect(&controller, SIGNAL(drawFitnessGraph(double,double,double,int)), &view, SLOT(drawFitnessGraph(double,double,double,int)));
    QObject::connect(&controller, SIGNAL(updateBest(vectorSquares)), &view, SIGNAL(updateBest(vectorSquares)));
    QObject::connect(&view, SIGNAL(startStepSimulation(Settings)), &controller, SLOT(beginStepSimulation(Settings)));
    QObject::connect(&view, SIGNAL(startContinousSimulation(Settings)), &controller, SLOT(beginContinousSimulation(Settings)));
    QObject::connect(&view, SIGNAL(resetSimulation()), &controller, SLOT(simulationReset()));

    view.show();
    return a.exec();
}

