#include "controller.h"

Controller::Controller(QObject *parent) :
    QObject(parent), isSimulationStarted(false)
{
    srand(time(0));
}

void Controller::beginContinousSimulation(Settings settings)
{
    if(isSimulationStarted == false)
    {
        isSimulationStarted = true;
        continousSimulation = new ContinuousSimulation(settings);
        continousSimulation->start();
    }
    else //wątek jest uruchomiony, co oznacza zatrzymanie, lub wznowienie watku
    {
        if(continousSimulation->isWorking() == true)
            continousSimulation->pause();
        else
            continousSimulation->resume();
    }
}

void Controller::nextStep()
{

}

void Controller::pause()
{

}

void Controller::restart()
{

}

void Controller::createConnections()
{
    connect(continousSimulation, SIGNAL(continousSimulationStarted()), this, SIGNAL(continousSimulationStarted()));
    connect(stepedSimulation, SIGNAL(stepSimulationStarted()), this, SIGNAL(stepSimulationStarted()));
}


void Controller::beginStepSimulation(Settings settings)
{
    if(isSimulationStarted == false)
    {
        isSimulationStarted = true;
        stepedSimulation = new StepedSimulation(settings);
        stepedSimulation->start();
    }
    else //watek jest juz uruchominy to oznacza kolejny krok
    {
        stepedSimulation->nextStep();
    }
}

