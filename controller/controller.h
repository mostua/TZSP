#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include "../model/model.h"
#include <QDebug>
using namespace std;

class Controller : public QThread
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    Controller* thread;
signals:
    void returnIteration(QString value);
public slots:
    void beginSimulation(unsigned int size);
public:
    void run();
};

#endif // CONTROLLER_H
