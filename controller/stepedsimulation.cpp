#include "stepedsimulation.h"

StepedSimulation::StepedSimulation(QObject *parent) :
    QThread(parent), isWorkingValue(false)
{
}

void StepedSimulation::run()
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
    emit stepSimulationStarted();
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
    } while (model.population->countFitness(&best) != 0);
    textToShow.clear();
    textToShow = "Result: fitness = " + QString("%1").arg(model.population->countFitness(&best));
    qDebug() << textToShow;
    //emit returnIteration(textToShow);
}

void StepedSimulation::nextStep()
{
    mutexIsWorking.unlock();
}
