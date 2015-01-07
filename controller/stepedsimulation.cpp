#include "stepedsimulation.h"

StepedSimulation::StepedSimulation(Model *model, QObject *parent) :
    QThread(parent), model(model), isWorkingValue(false), end(false), isLocked(false)
{
    mutexIsWorking = new QMutex;
    mutexEnd = new QMutex;
    mutexIsLocked = new QMutex;
}

void StepedSimulation::setSettings(Settings _settings)
{
    settings = _settings;
}

void StepedSimulation::clear()
{
    delete mutexIsWorking;
    delete mutexEnd;
    delete mutexIsLocked;
    mutexIsWorking = new QMutex;
    mutexEnd = new QMutex;
    mutexIsLocked = new QMutex;
    isWorkingValue = false;
    isLocked = false;
    end = false;
}


StepedSimulation::~StepedSimulation()
{
    clear();
}

void StepedSimulation::run()
{
    srand(time(0));
    qDebug() << "Thread started";
    //substitute
    int reproductionAvaiable = settings.getMi();
     model->population = new Population(settings.getSquareSize(), settings.getMi(), settings.getLambda(), settings.getMutationTypeFunction(), settings.getSquareTypeFunction(), settings.getSelectionTypeFunction(), settings.getReproductionTypeFunction(), settings.getAlgorithmType() == Settings::algorithmType::alphaPlusMi ? 0 : 1);
    Square best(settings.getSquareSize(), settings.getSquareTypeFunction());
    int i = 1;
    QString textToShow;
    isWorkingValue = true;
    bool localEnd = false;
    emit stepSimulationStarted();
    do
    {
        mutexIsWorking->lock();
        mutexIsLocked->lock();
        isLocked = true;
        mutexIsLocked->unlock();
        mutexEnd->lock();
        if(end == true)
            localEnd = true;
        mutexEnd->unlock();
        if(localEnd == true)
        {
            break;
        }
        for(int j = 0; j  < settings.getSimulationParameter(); ++j)
        {
            model->population->generateNextPopulation();
            best = model->population->getBest();
            textToShow.clear();
            textToShow = "Iteration " +  QString("%1").arg(i++) + " best far now " + QString("%1").arg(model->population->countFitness(&best)) + " Population size: " + QString("%1").arg(model->population->getPopulationSize());
            emit drawFitnessGraph(i, best.countFitness(), model->population->populationAverage(), 0);
            emit drawNumberOfIndivuals(model->population->howManySpecificFitness(), 0);
            emit updateBest(model->population->getSomeBest(HOW_MANY_BEST_SHOW));
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
    mutexIsWorking->unlock();
    return;
}

void StepedSimulation::nextStep()
{
    mutexIsLocked->lock();
    if (isLocked == true)
    {
        isLocked = false;
        mutexIsWorking->unlock();
    }
    mutexIsLocked->unlock();
}

void StepedSimulation::killMe()
{
    mutexEnd->lock();
    end = true;
    mutexEnd->unlock();
}
