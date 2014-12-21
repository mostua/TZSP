#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    srand(time(0));
}


void Controller::beginSimulation(Settings settings)
{
    //emit returnIteration(QString("Simulation begun size = %1").arg(size));
    thread = new continuousSimulation;
    //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    //connect(thread, SIGNAL(returnIteration(QString)), this, SIGNAL(returnIteration(QString)));
    //connect(this, SIGNAL(pauseOrResumeSimulationSignal()), thread, SLOT(pauseOrResumeSlot()));
    //connect(thread, SIGNAL(simulationStarted()), this, SIGNAL(simulationStarted()));
    thread->start();
}

