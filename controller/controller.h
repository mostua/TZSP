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
    explicit Controller(QObject *parent = 0);
    ContinuousSimulation * continousSimulation;
    StepedSimulation * stepedSimulation;
signals:
    void stepSimulationStarted();
    void continousSimulationStarted();
/*    void pauseOrResumeSimulationSignal();*/
public slots:
    void beginStepSimulation(Settings settings);
    void beginContinousSimulation(Settings settings);
    void nextStep(); //slot wywolywany przy symulacji krokowej
    void pause(); //slot wywolywany przy symulacji ciaglej
    void restart();
private:
    bool isSimulationStarted;
    void createConnections();
};

#endif // CONTROLLER_H
