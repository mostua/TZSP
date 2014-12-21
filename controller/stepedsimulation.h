#ifndef STEPEDSIMULATION_H
#define STEPEDSIMULATION_H

#include <QThread>

class stepedSimulation : public QThread
{
    Q_OBJECT
public:
    explicit stepedSimulation(QObject *parent = 0);

signals:

public slots:

};

#endif // STEPEDSIMULATION_H
