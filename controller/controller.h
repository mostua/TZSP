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
    QThread* thread;
signals:
    void simulationStarted();
/*    void pauseOrResumeSimulationSignal();*/
public slots:
    void beginSimulation(Settings settings);
    //void pauseOrResumeSimulationSlot();

};

#endif // CONTROLLER_H
