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
    explicit StepedSimulation(Model * model, Settings, QObject *parent = 0);
    ~StepedSimulation();
signals:
    void stepSimulationStarted();
    void drawFitnessGraph(double iteration, double best, double average, int graph);
    void drawNumberOfIndivuals(vectorPairs, int graph);
    void updateBest(vectorSquares best);
public slots:
    void run();
    void nextStep();
    void killMe();
private:
    Model * model;
    Settings settings;
    QMutex mutexIsWorking;
    QMutex mutexEnd;
    bool isWorkingValue;
    bool end;
};

#endif // STEPEDSIMULATION_H
