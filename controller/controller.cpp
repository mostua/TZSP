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
        threadSaver.lock();
        isSimulationStarted = true;
        whichStarted = continous;
        continousSimulation = new ContinuousSimulation(model, settings);
        connect(continousSimulation, SIGNAL(started()), this, SIGNAL(continousSimulationStarted()));
        connect(continousSimulation, SIGNAL(finished()), this, SLOT(continousSimulationFinished()));
        connect(continousSimulation, SIGNAL(drawFitnessGraph(double,double,double,int)), this, SIGNAL(drawFitnessGraph(double,double,double,int)));
        connect(continousSimulation, SIGNAL(drawNumberOfIndivuals(vectorPairs,int)), this, SIGNAL(drawNumberOfIndivuals(vectorPairs,int)));
        connect(continousSimulation, SIGNAL(updateBest(vectorSquares)), this, SIGNAL(updateBest(vectorSquares)));
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
    emit simulationReseted();
}

void Controller::continousSimulationFinished()
{
    qDebug() << "disconnectingContinousSimulation";
    disconnect(continousSimulation, SIGNAL(started()), this, SIGNAL(continousSimulationStarted()));
    disconnect(continousSimulation, SIGNAL(finished()), this, SLOT(continousSimulationFinished()));
    disconnect(continousSimulation, SIGNAL(drawFitnessGraph(double,double,double,int)), this, SIGNAL(drawFitnessGraph(double,double,double,int)));
    disconnect(continousSimulation, SIGNAL(drawNumberOfIndivuals(vectorPairs)), this, SIGNAL(drawNumberOfIndivuals(vectorPairs,int)));
    disconnect(continousSimulation, SIGNAL(updateBest(vectorSquares)), this, SIGNAL(updateBest(vectorSquares)));
    isSimulationStarted = false;
    delete continousSimulation;
    threadSaver.unlock();
}

void Controller::stepSimulationFinished()
{
    disconnect(stepedSimulation, SIGNAL(started()), this, SIGNAL(stepSimulationStarted()));
    disconnect(stepedSimulation, SIGNAL(finished()), this, SLOT(stepSimulationFinished()));
    disconnect(stepedSimulation, SIGNAL(drawFitnessGraph(double,double,double,int)), this, SIGNAL(drawFitnessGraph(double,double,double,int)));
    disconnect(stepedSimulation, SIGNAL(drawNumberOfIndivuals(vectorPairs,int)), this, SIGNAL(drawNumberOfIndivuals(vectorPairs ,int)));
    disconnect(stepedSimulation, SIGNAL(updateBest(vectorSquares)), this, SIGNAL(updateBest(vectorSquares)));
    isSimulationStarted = false;
    delete stepedSimulation;
    threadSaver.unlock();
}


void Controller::beginStepSimulation(Settings settings)
{
    if(isSimulationStarted == false)
    {
        threadSaver.lock();
        isSimulationStarted = true;
        whichStarted = step;
        stepedSimulation = new StepedSimulation(model, settings);
        connect(stepedSimulation, SIGNAL(started()), this, SIGNAL(stepSimulationStarted()));
        connect(stepedSimulation, SIGNAL(finished()), this, SLOT(stepSimulationFinished()));
        connect(stepedSimulation, SIGNAL(drawFitnessGraph(double,double,double,int)), this, SIGNAL(drawFitnessGraph(double,double,double,int)));
        connect(stepedSimulation, SIGNAL(drawNumberOfIndivuals(vectorPairs)), this, SIGNAL(drawNumberOfIndivuals(vectorPairs,int)));
        connect(stepedSimulation, SIGNAL(updateBest(vectorSquares)), this, SIGNAL(updateBest(vectorSquares)));
        stepedSimulation->start();
    }
    else if(whichStarted == step) //watek jest juz uruchominy (i dotyczy symulacji krokowej) to oznacza kolejny krok
    {
        stepedSimulation->nextStep();
    }
}

