#ifndef CONTINUOUSSIMULATION_H
#define CONTINUOUSSIMULATION_H

#include <QThread>

class continuousSimulation : public QThread
{
    Q_OBJECT
public:
    explicit continuousSimulation(QObject *parent = 0);

signals:

public slots:

};

#endif // CONTINUOUSSIMULATION_H
