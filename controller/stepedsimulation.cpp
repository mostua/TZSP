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
     model->population = new Population(settings.getSquareSize(), settings.getMi(), settings.getLambda(), settings.getMinSigma(), settings.getMaxSigma(), settings.getMutationTypeFunction(), settings.getSquareTypeFunction(), settings.getSelectionTypeFunction(), settings.getReproductionTypeFunction(), settings.getAlgorithmType() == Settings::algorithmType::alphaPlusMi ? 0 : 1);
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
        for(int j = 0; j  < settings.getSimulationParameter(); ++j)
        {
            mutexEnd->lock();
            if(end == true)
                localEnd = true;
            mutexEnd->unlock();
            if(localEnd == true)
            {
                break;
            }
            model->population->generateNextPopulation();
            best = model->population->getBest();
            textToShow.clear();
            textToShow = "Iteration " +  QString("%1").arg(i) + " best far now " + QString("%1").arg(model->population->countFitness(&best)) + " Population size: " + QString("%1").arg(model->population->getPopulationSize());
            emit drawFitnessGraph(i, best.countFitness(), model->population->populationAverage(), 0);
            emit drawNumberOfIndivuals(model->population->howManySpecificFitness(), 0);
            emit updateBest(model->population->getSomeBest(HOW_MANY_BEST_SHOW));
            qDebug() << textToShow;
            if(settings.getAddNewIndividualsInterval() > 0 && i % settings.getAddNewIndividualsInterval() == 0)
                model->population->addNewIndividuals(settings.getAddNewIndividualsHowMany());
            if(settings.getLimitPopulationValue() > 0)
                model->population->cutPopulationToSomeBest(settings.getLimitPopulationValue());
            if(model->population->countFitness(&best) == 0)
                break;
            i++;
        }
        if(localEnd == true)
        {
            break;
        }
    } while (model->population->countFitness(&best) != 0);
    textToShow.clear();
    textToShow = "Result: fitness = " + QString("%1").arg(model->population->countFitness(&best)) + " Population size: " + QString("%1").arg(model->population->getPopulationSize());
    qDebug() << textToShow;
    mutexIsLocked->lock();
    isLocked = false;
    mutexIsLocked->unlock();
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
    nextStep();
    mutexEnd->unlock();
}
