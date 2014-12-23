#include "continuoussimulation.h"


ContinuousSimulation::ContinuousSimulation(QObject *parent) :
    QThread(parent), isWorkingValue(false)
{
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
    int reproductionAvaiable = 2500;

    Model model;
    model.population = new Population(3,reproductionAvaiable, mutation::swapToPoints, fitness::onlyRowsAndColumns, reproduction::reproductionFunction);
    Square best(3);
    int i = 1;
    QString textToShow;
    isWorkingValue = true;
    emit continousSimulationStarted();
    do
    {
        mutexIsWorking.lock();
        model.population->generateNextPopulation(100);
        best = model.population->getBest();
        textToShow.clear();
        textToShow = "Iteration " +  QString("%1").arg(i++) + " best far now " + QString("%1").arg(model.population->countFitness(&best));
        qDebug() << textToShow;
        if(i % 100 == 0)
            model.population->addNewIndividuals(reproductionAvaiable);
        mutexIsWorking.unlock();
    } while (model.population->countFitness(&best) != 0);
    textToShow.clear();
    textToShow = "Result: fitness = " + QString("%1").arg(model.population->countFitness(&best));
    qDebug() << textToShow;
    //emit returnIteration(textToShow);
}

void ContinuousSimulation::pause()
{
    mutexIsWorking.lock();
    isWorkingValue = false;
}


void ContinuousSimulation::resume()
{
    isWorkingValue = true;
    mutexIsWorking.unlock();
}
