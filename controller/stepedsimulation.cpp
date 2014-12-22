#include "stepedsimulation.h"

StepedSimulation::StepedSimulation(QObject *parent) :
    QThread(parent)
{
}

void StepedSimulation::run()
{
    srand(time(0));
    qDebug() << "Thread started";
    //substitute
    int reproductionAvaiable = 2500;

    Model<4> model;
    model.population = new Population<4>(reproductionAvaiable, mutation::swapToPoints, fitness::onlyRowsAndColumns, reproduction::reproductionFunction);
    Square<4> best;
    int i = 1;
    QString textToShow;
    isWorking = true;
    emit stepSimulationStarted();
    do
    {
        saveIsWorking.lock();
        while(isWorking == false)
            canStartWorking.wait(&saveIsWorking);
        model.population->generateNextPopulation(100);
        best = model.population->getBest(fitness::onlyRowsAndColumns);
        textToShow.clear();
        textToShow = "Iteration " +  QString("%1").arg(i++) + " best far now " + QString("%1").arg(fitness::onlyRowsAndColumns(best));
        qDebug() << textToShow;
        if(i % 100 == 0)
            model.population->addNewIndividuals(reproductionAvaiable);
    } while (fitness::onlyRowsAndColumns(best) != 0);
    textToShow.clear();
    textToShow = "Result: fitness = " + QString("%1").arg(fitness::onlyRowsAndColumns(best));
    qDebug() << textToShow;
    //emit returnIteration(textToShow);
}

void StepedSimulation::nextStep()
{
    saveIsWorking.unlock();
}
