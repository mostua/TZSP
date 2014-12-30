#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <cstdlib>
#include <ctime>
#include "../model/model.h"
#include "../model/settings.h"
#include "continuoussimulation.h"
#include "stepedsimulation.h"

using namespace std;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Model * model, QObject *parent = 0);
    ContinuousSimulation * continousSimulation;
    StepedSimulation * stepedSimulation;
signals:
    void stepSimulationStarted();
    void continousSimulationStarted();
    void simulationReseted();
    void drawFitnessGraph(double iteration, double best, double average, int graph);
public slots:
    void beginStepSimulation(Settings settings);
    void beginContinousSimulation(Settings settings);
    void simulationReset();
private slots:
    void continousSimulationFinished();
    void stepSimulationFinished();
private:
    QMutex threadSaver;
    Model * model;
    enum startedSimulation{step,continous};
    startedSimulation whichStarted;
    bool isSimulationStarted;
    void createConnections();
};

#endif // CONTROLLER_H
