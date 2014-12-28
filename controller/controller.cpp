#include "controller.h"

Controller::Controller(Model *model, QObject *parent) :
    QObject(parent), model(model), isSimulationStarted(false)
{
    srand(time(0));

}

void Controller::beginContinousSimulation(Settings settings)
{
    if(isSimulationStarted == false)
    {
        isSimulationStarted = true;
        whichStarted = continous;
        continousSimulation = new ContinuousSimulation(model, settings);
        connect(continousSimulation, SIGNAL(started()), this, SIGNAL(continousSimulationStarted()));
        connect(continousSimulation, SIGNAL(finished()), this, SLOT(continousSimulationFinished()));
        continousSimulation->start();
    }
    else if(whichStarted == continous) //wątek jest uruchomiony (i dotyczy symulacji ciaglej), co oznacza zatrzymanie, lub wznowienie watku
    {
        if(continousSimulation->isWorking() == true)
            continousSimulation->pause();
        else
            continousSimulation->resume();
    }
}

void Controller::simulationReset()
{
    if(isSimulationStarted == true)
    {
        if(whichStarted == continous){
            continousSimulation->killMe();
        }
        if(whichStarted == step){ //ta metoda nie dziala dobrze
            stepedSimulation->killMe();
        }
    }
}

void Controller::continousSimulationFinished()
{
    qDebug() << "disconnectingContinousSimulation";
    disconnect(continousSimulation, SIGNAL(started()), this, SIGNAL(continousSimulationStarted()));
    disconnect(continousSimulation, SIGNAL(finished()), this, SLOT(continousSimulationFinished()));
    isSimulationStarted = false;
    delete continousSimulation;
}

void Controller::stepSimulationFinished()
{
    disconnect(stepedSimulation, SIGNAL(started()), this, SIGNAL(stepSimulationStarted()));
    disconnect(stepedSimulation, SIGNAL(finished()), this, SLOT(stepSimulationFinished()));
    isSimulationStarted = false;
    delete stepedSimulation;
}


void Controller::beginStepSimulation(Settings settings)
{
    if(isSimulationStarted == false)
    {
        isSimulationStarted = true;
        whichStarted = step;
        stepedSimulation = new StepedSimulation(model, settings);
        connect(stepedSimulation, SIGNAL(started()), this, SIGNAL(stepSimulationStarted()));
        connect(stepedSimulation, SIGNAL(finished()), this, SLOT(stepSimulationFinished()));
        stepedSimulation->start();
    }
    else if(whichStarted == step) //watek jest juz uruchominy (i dotyczy symulacji krokowej) to oznacza kolejny krok
    {
        stepedSimulation->nextStep();
    }
}

