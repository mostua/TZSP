#include "continuoussimulation.h"


ContinuousSimulation::ContinuousSimulation(Model *model, QObject *parent) :
    QThread(parent), model(model), isWorkingValue(false), end(false)
{

}

ContinuousSimulation::~ContinuousSimulation()
{
    clear();
}

bool ContinuousSimulation::isWorking() const
{
    return isWorkingValue;
}

void ContinuousSimulation::setSettings(Settings _settings)
{
    settings = _settings;
}

void ContinuousSimulation::clear()
{
    if (mutexIsWorking.tryLock() == false)
        mutexIsWorking.unlock();
    if (mutexEnd.tryLock() == false)
        mutexEnd.unlock();
    isWorkingValue = false;
    end = false;
}


void ContinuousSimulation::run()
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
    emit continousSimulationStarted();
    do
    {
        mutexIsWorking.lock();
        if(end == true)
            break;
        model->population->generateNextPopulation();
        best = model->population->getBest();
        textToShow.clear();
        textToShow = "Iteration " +  QString("%1").arg(i++) + " best far now " + QString("%1").arg(model->population->countFitness(&best)) + " Population size: " + QString("%1").arg(model->population->getPopulationSize());
        emit drawFitnessGraph(i, best.countFitness(), model->population->populationAverage(), 0);
        emit drawNumberOfIndivuals(model->population->howManySpecificFitness(), 0);
        emit updateBest(model->population->getSomeBest(HOW_MANY_BEST_SHOW));
        qDebug() << textToShow;
        if(i % 100 == 10)
            model->population->addNewIndividuals(reproductionAvaiable);
        i++;
        mutexIsWorking.unlock();
    } while (model->population->countFitness(&best) != 0);
    textToShow.clear();
    textToShow = "Result: fitness = " + QString("%1").arg(model->population->countFitness(&best));
    qDebug() << textToShow;
    return;
}

void ContinuousSimulation::pause()
{
    mutexIsWorking.lock();
    isWorkingValue = false;
}

void ContinuousSimulation::killMe()
{
    qDebug() << "Continous Kill Me";
    mutexIsWorking.lock();
    end = true;
    mutexIsWorking.unlock();
}


void ContinuousSimulation::resume()
{
    isWorkingValue = true;
    mutexIsWorking.unlock();
}
