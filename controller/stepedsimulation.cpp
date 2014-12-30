#include "stepedsimulation.h"

StepedSimulation::StepedSimulation(Model *model, Settings _settings, QObject *parent) :
    QThread(parent), model(model), settings(_settings), isWorkingValue(false), end(false)
{
}


StepedSimulation::~StepedSimulation()
{
    if (mutexIsWorking.tryLock() == false)
        mutexIsWorking.unlock();
    if (mutexEnd.tryLock() == false)
        mutexEnd.unlock();
}

void StepedSimulation::run()
{
    srand(time(0));
    qDebug() << "Thread started";
    //substitute
    int reproductionAvaiable = settings.getMi();

     model->population = new Population(settings.getSquareSize(), settings.getMi(), settings.getLambda(), settings.getMutationTypeFunction(), settings.getSquareTypeFunction(), settings.getSelectionTypeFunction(), settings.getReproductionTypeFunction());
    Square best(settings.getSquareSize(), settings.getSquareTypeFunction());
    int i = 1;
    QString textToShow;
    isWorkingValue = true;
    emit stepSimulationStarted();
    do
    {
        mutexIsWorking.lock();
        mutexEnd.lock();
        if(end == true)
            return;
        mutexEnd.unlock();
        for(int j = 0; j  < settings.getSimulationParameter(); ++j)
        {
            model->population->generateNextPopulation();
            
            best = model->population->getBest();
            textToShow.clear();
            textToShow = "Iteration " +  QString("%1").arg(i++) + " best far now " + QString("%1").arg(model->population->countFitness(&best)) + " Population size: " + QString("%1").arg(model->population->getPopulationSize());
            qDebug() << textToShow;
            if(i % 100 == 0)
                model->population->addNewIndividuals(reproductionAvaiable);
            if(model->population->countFitness(&best) == 0)
                break;
        }
    } while (model->population->countFitness(&best) != 0);
    textToShow.clear();
    textToShow = "Result: fitness = " + QString("%1").arg(model->population->countFitness(&best)) + " Population size: " + QString("%1").arg(model->population->getPopulationSize());
    qDebug() << textToShow;
    //emit returnIteration(textToShow);
}

void StepedSimulation::nextStep()
{
    if (mutexIsWorking.tryLock() == false)
        mutexIsWorking.unlock();
}

void StepedSimulation::killMe()
{
    mutexEnd.lock();
    end = true;
    mutexEnd.unlock();
    if(mutexIsWorking.tryLock() == false)
        mutexIsWorking.unlock();
}
