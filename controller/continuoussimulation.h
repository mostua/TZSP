#ifndef CONTINUOUSSIMULATION_H
#define CONTINUOUSSIMULATION_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include <ctime>
#include <cstdlib>
#include "../model/model.h"

class ContinuousSimulation : public QThread
{
    Q_OBJECT
public:
    explicit ContinuousSimulation(QObject *parent = 0);
    bool isWorking() const;
signals:
    void continousSimulationStarted();
public slots:
    void run();
    void pause();
    void resume();
private:
    QMutex mutexIsWorking;
    //QMutexLocker lockerIsWorking;
    //QWaitCondition canStartWorking;
    bool isWorkingValue;
};

#endif // CONTINUOUSSIMULATION_H
