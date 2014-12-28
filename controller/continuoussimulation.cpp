#include "continuoussimulation.h"


ContinuousSimulation::ContinuousSimulation(Model *model, Settings _settings, QObject *parent) :
    QThread(parent), model(model), settings(_settings), isWorkingValue(false), end(false)
{
}

ContinuousSimulation::~ContinuousSimulation()
{
    mutexIsWorking.unlock();
    mutexEnd.unlock();
}

bool ContinuousSimulation::isWorking() const
{
    return isWorkingValue;
}

void ContinuousSimulation::run()
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
    emit continousSimulationStarted();
    do
    {
        mutexIsWorking.lock();
        if(end == true)
            break;
        model->population->generateNextPopulation(settings.getMi());
        best = model->population->getBest();
        textToShow.clear();
        textToShow = "Iteration " +  QString("%1").arg(i++) + " best far now " + QString("%1").arg(model->population->countFitness(&best)) + " Population size: " + QString("%1").arg(model->population->getPopulationSize());
        qDebug() << textToShow;
        if(i % 100 == 0)
            model->population->addNewIndividuals(reproductionAvaiable);
        i++;
        mutexIsWorking.unlock();
    } while (model->population->countFitness(&best) != 0);
    textToShow.clear();
    textToShow = "Result: fitness = " + QString("%1").arg(model->population->countFitness(&best));
    qDebug() << textToShow;
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
