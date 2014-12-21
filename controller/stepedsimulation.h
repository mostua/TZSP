#ifndef STEPEDSIMULATION_H
#define STEPEDSIMULATION_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
#include "../model/model.h"


class stepedSimulation : public QThread
{
    Q_OBJECT
public:
    explicit stepedSimulation(QObject *parent = 0);

signals:

public slots:
    void run();
private:
    QMutex saveIsWorking;
    //QMutexLocker lockerIsWorking;
    QWaitCondition canStartWorking;
    bool isWorking;
};

#endif // STEPEDSIMULATION_H
