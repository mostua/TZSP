#include "controller.h"

Controller::Controller(Model *model, QObject *parent) :
    QObject(parent), model(model), isSimulationStarted(false)
{
    srand(time(0));
    continousSimulation = new ContinuousSimulation(model);
    stepedSimulation = new StepedSimulation(model);
    createConnections();
}

void Controller::beginContinousSimulation(Settings settings)
{
    if(isSimulationStarted == false)
    {
        threadSaver.lock();
        isSimulationStarted = true;
        whichStarted = continous;
        continousSimulation->setSettings(settings);
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
        if(whichStarted == step){
            stepedSimulation->killMe();
        }
    }

}

void Controller::continousSimulationFinished()
{
    qDebug() << "disconnectingContinousSimulation";
    continousSimulation->clear();
    threadSaver.unlock();
    isSimulationStarted = false;
    emit simulationReseted();
}

void Controller::stepSimulationFinished()
{
    qDebug() << "disconnectingStepedSimulation";
    stepedSimulation->clear();
    threadSaver.unlock();
    isSimulationStarted = false;
    emit simulationReseted();
}

void Controller::createConnections()
{
    /* Połączenia symulacji ciągłej */
    connect(continousSimulation, SIGNAL(started()), this, SIGNAL(continousSimulationStarted()));
    connect(continousSimulation, SIGNAL(finished()), this, SLOT(continousSimulationFinished()));
    connect(continousSimulation, SIGNAL(drawFitnessGraph(double,double,double,int)), this, SIGNAL(drawFitnessGraph(double,double,double,int)));
    connect(continousSimulation, SIGNAL(drawNumberOfIndivuals(vectorPairs,int)), this, SIGNAL(drawNumberOfIndivuals(vectorPairs,int)));
    connect(continousSimulation, SIGNAL(updateBest(vectorSquares)), this, SIGNAL(updateBest(vectorSquares)));


    /* Połączenia symulacji krokowej */
    connect(stepedSimulation, SIGNAL(started()), this, SIGNAL(stepSimulationStarted()));
    connect(stepedSimulation, SIGNAL(finished()), this, SLOT(stepSimulationFinished()));
    connect(stepedSimulation, SIGNAL(drawFitnessGraph(double,double,double,int)), this, SIGNAL(drawFitnessGraph(double,double,double,int)));
    connect(stepedSimulation, SIGNAL(drawNumberOfIndivuals(vectorPairs,int)), this, SIGNAL(drawNumberOfIndivuals(vectorPairs,int)));
    connect(stepedSimulation, SIGNAL(updateBest(vectorSquares)), this, SIGNAL(updateBest(vectorSquares)));
}


void Controller::beginStepSimulation(Settings settings)
{
    if(isSimulationStarted == false)
    {
        threadSaver.lock();
        isSimulationStarted = true;
        whichStarted = step;
        stepedSimulation->setSettings(settings);
        stepedSimulation->start();

    }
    else if(whichStarted == step) //watek jest juz uruchominy (i dotyczy symulacji krokowej) to oznacza kolejny krok
    {
        stepedSimulation->nextStep();
    }
}

