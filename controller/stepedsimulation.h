#ifndef STEPEDSIMULATION_H
#define STEPEDSIMULATION_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <ctime>
#include <cstdlib>
#include "../model/model.h"
#include "../model/settings.h"


class StepedSimulation : public QThread
{
    Q_OBJECT
public:
    explicit StepedSimulation(Settings, QObject *parent = 0);

signals:
    void stepSimulationStarted();
public slots:
    void run();
    void nextStep();
private:
    Settings settings;
    QMutex mutexIsWorking;
    QWaitCondition canStartWorking;
    bool isWorkingValue;
};

#endif // STEPEDSIMULATION_H
