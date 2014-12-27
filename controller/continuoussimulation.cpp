#include "continuoussimulation.h"


ContinuousSimulation::ContinuousSimulation(Settings _settings, QObject *parent) :
    QThread(parent), settings(_settings), isWorkingValue(false)
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
    int reproductionAvaiable = settings.getAlpha();

    Model model;
    model.population = new Population(settings.getSquareSize(),reproductionAvaiable, settings.getMutationTypeFunction(), settings.getSquareTypeFunction(), settings.getReproductionTypeFunction());
    Square best(settings.getSquareSize());
    int i = 1;
    QString textToShow;
    isWorkingValue = true;
    emit continousSimulationStarted();
    do
    {
        mutexIsWorking.lock();
        model.population->generateNextPopulation(settings.getMi());
        best = model.population->getBest();
        textToShow.clear();
        textToShow = "Iteration " +  QString("%1").arg(i++) + " best far now " + QString("%1").arg(model.population->countFitness(&best));
        qDebug() << textToShow;
        if(i % 100 == 0)
            model.population->addNewIndividuals(reproductionAvaiable);
        i++;
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
