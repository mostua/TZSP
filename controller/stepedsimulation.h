#ifndef STEPEDSIMULATION_H
#define STEPEDSIMULATION_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <ctime>
#include <cstdlib>
#include "../model/model.h"

class StepedSimulation : public QThread
{
    Q_OBJECT
public:
    explicit StepedSimulation(QObject *parent = 0);

signals:
    void stepSimulationStarted();
public slots:
    void run();
    void nextStep();
private:
    QMutex mutexIsWorking;
    //QMutexLocker lockerIsWorking;
    QWaitCondition canStartWorking;
    bool isWorkingValue;
};

#endif // STEPEDSIMULATION_H
