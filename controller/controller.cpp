#include "controller.h"

Controller::Controller(QObject *parent) :
    QThread(parent)
{
}

void Controller::run()
{
    qDebug() << "Thread started";
    //substitute
    int reproductionAvaiable = 2500;

    Model<3> model;
    model.population = new Population<3>(reproductionAvaiable, mutation::swapToPoints, fitness::diagonalsAreImportant, reproduction::reproductionFunction);
    Square<3> best;
    int i = 1;
    QString textToShow;
    do
    {
        model.population->generateNextPopulation(50);
        best = model.population->getBest(fitness::diagonalsAreImportant);
        textToShow.clear();
        textToShow = "Iteration " +  QString("%1").arg(i++) + " best far now " + QString("%1").arg(fitness::diagonalsAreImportant(best));
        emit returnIteration(textToShow);
        textToShow = "Test";
        emit returnIteration(textToShow);
    } while (fitness::diagonalsAreImportant(best) != 0);
    textToShow.clear();
    textToShow = "Result: fitness = " + QString("%1").arg(fitness::diagonalsAreImportant(best));
    emit returnIteration(textToShow);
}

void Controller::beginSimulation(unsigned int size)
{
    emit returnIteration(QString("Simulation begun size = %1").arg(size));
    thread = new Controller(this);
    //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(thread, SIGNAL(returnIteration(QString)), this, SIGNAL(returnIteration(QString)));
    thread->start();
}
