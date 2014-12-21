#ifndef CONTINUOUSSIMULATION_H
#define CONTINUOUSSIMULATION_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include "../model/model.h"

class continuousSimulation : public QThread
{
    Q_OBJECT
public:
    explicit continuousSimulation(QObject *parent = 0);

signals:
    void simulationStarted();
public slots:
    void run();
private:
    QMutex saveIsWorking;
    //QMutexLocker lockerIsWorking;
    QWaitCondition canStartWorking;
    bool isWorking;
};

#endif // CONTINUOUSSIMULATION_H
