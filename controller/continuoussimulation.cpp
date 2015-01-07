#include "continuoussimulation.h"


ContinuousSimulation::ContinuousSimulation(Model *model, QObject *parent) :
    QThread(parent), model(model), isWorkingValue(false), end(false)
{
    mutexIsWorking = new QMutex;
    mutexEnd = new QMutex;
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
    delete mutexIsWorking;
    delete mutexEnd;
    mutexIsWorking = new QMutex;
    mutexEnd = new QMutex;
    isWorkingValue = false;
    end = false;
}


void ContinuousSimulation::run()
{
    srand(time(0));
    qDebug() << "Thread started";
    //substitute
    int reproductionAvaiable = settings.getMi();
    model->population = new Population(settings.getSquareSize(), settings.getMi(), settings.getLambda(), settings.getMutationTypeFunction(), settings.getSquareTypeFunction(), settings.getSelectionTypeFunction(), settings.getReproductionTypeFunction(), settings.getAlgorithmType() == Settings::algorithmType::alphaPlusMi ? 0 : 1);
    Square best(settings.getSquareSize(), settings.getSquareTypeFunction());
    int i = 1;
    QString textToShow;

    bool localEnd = false;
    emit continousSimulationStarted();
    do
    {
        mutexIsWorking->lock();
        isWorkingValue = true;
        mutexEnd->lock();
        if(end == true)
            localEnd = true;
        mutexEnd->unlock();
        if(localEnd)
        {
            mutexIsWorking->unlock();
            break;
        }
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
        mutexIsWorking->unlock();
    } while (model->population->countFitness(&best) != 0);
    textToShow.clear();
    textToShow = "Result: fitness = " + QString("%1").arg(model->population->countFitness(&best));
    qDebug() << textToShow;
    return;
}

void ContinuousSimulation::pause()
{
    mutexIsWorking->lock();
    isWorkingValue = false;
}

void ContinuousSimulation::killMe()
{
    qDebug() << "Continous Kill Me";
    mutexEnd->lock();
    end = true;
    if(isWorkingValue == false)
        resume();
    mutexEnd->unlock();

}


void ContinuousSimulation::resume()
{
    isWorkingValue = true;
    mutexIsWorking->unlock();
}
