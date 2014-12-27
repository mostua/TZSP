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
    explicit ContinuousSimulation(Settings, QObject *parent = 0);
    bool isWorking() const;
signals:
    void continousSimulationStarted();
public slots:
    void run();
    void pause();
    void resume();
private:
    QMutex mutexIsWorking;
    Settings settings;
    bool isWorkingValue;
};

#endif // CONTINUOUSSIMULATION_H
