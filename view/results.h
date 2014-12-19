#ifndef RESULTS_H
#define RESULTS_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QPushButton>
#include "libraries/qcustomplot.h"

class Results : public QWidget
{
    Q_OBJECT
public:
    explicit Results(QWidget *parent = 0);
signals:
    void beginSimulationClicked();
public slots:

private slots:
    void swapCharts();
private:
    /*Layout widgetu*/
    QGridLayout *widgetLayout;
    /*Grupa zawierające przyciski do wyboru symulacji */
    QGroupBox* simulationOptionsBox;
    /*Grupa zawierające przyciski do wyboru wykresu */
    QGroupBox* chartTypeBox;
    /*Przyciski od wyboru symulacji */
    QRadioButton* simulationOptionsButtons[3];
    /*Suwaki od wyboru parametrow symulacji */
    QSpinBox* simulationOptionsSpinBoxes[2];
    /*Przyciski od wyboru wykresu */
    QRadioButton* chartTypeButtons[2];
    /*Przycisk rozpoczynający symulacje */
    QPushButton *beginButton;
    /*Przycisk do zresetowania symulacji */
    QPushButton *resetButton;
    /*Widget z grafika */
    QCustomPlot *fitnessOnIterationChart;
    QCustomPlot *numberOnFitnessChart;
    void createWidgetItems();
    void setWidgetLayout();
    void createConnections();
};

#endif // RESULTS_H
