#include "stepedsimulation.h"

StepedSimulation::StepedSimulation(Model *model, Settings _settings, QObject *parent) :
    QThread(parent), model(model), settings(_settings), isWorkingValue(false), end(false)
{
}


StepedSimulation::~StepedSimulation()
{
    mutexIsWorking.unlock();
    mutexEnd.unlock();
}

void StepedSimulation::run()
{
    srand(time(0));
    qDebug() << "Thread started";
    //substitute
    int reproductionAvaiable = settings.getAlpha();

    model->population = new Population(settings.getSquareSize(),reproductionAvaiable, settings.getMutationTypeFunction(), settings.getSquareTypeFunction(), settings.getReproductionTypeFunction());
    Square best(settings.getSquareSize());
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
            model->population->generateNextPopulation(settings.getMi());
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
    mutexIsWorking.unlock();
}

void StepedSimulation::killMe()
{
    mutexEnd.lock();
    end = true;
    mutexEnd.unlock();
    if(mutexIsWorking.tryLock() == true)
        mutexIsWorking.unlock();
}
