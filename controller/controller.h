#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include "../model/model.h"
#include <QDebug>
using namespace std;

class Controller : public QThread
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    Controller* thread;
signals:
    void returnIteration(QString value);
public slots:
    void beginSimulation(unsigned int size)
    {
        emit returnIteration(QString("Simulation begun size = %1").arg(size));
        thread = new Controller(this);
        //connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        connect(thread, SIGNAL(returnIteration(QString)), this, SIGNAL(returnIteration(QString)));
        thread->start();
    }
public:
    void run()
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
};

#endif // CONTROLLER_H
