#ifndef CONTINUOUSSIMULATION_H
#define CONTINUOUSSIMULATION_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <ctime>
#include <cstdlib>
#include "../model/model.h"
#include "../model/settings.h"

class ContinuousSimulation : public QThread
{
    Q_OBJECT
public:
    explicit ContinuousSimulation(Model * model, Settings, QObject *parent = 0);
    ~ContinuousSimulation();
    bool isWorking() const;
signals:
    void continousSimulationStarted();
public slots:
    void run();
    void pause();
    void resume();
    void killMe();
private:
    QMutex mutexIsWorking;
    QMutex mutexEnd;
    Model * model;
    Settings settings;
    bool isWorkingValue;
    bool end;
};

#endif // CONTINUOUSSIMULATION_H
