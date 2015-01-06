#ifndef RESULTS_H
#define RESULTS_H

#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QPushButton>
#include "../libraries/qcustomplot.h"
#include "../model/model.h"
#include "../model/settings.h"

class Results : public QWidget
{
    Q_OBJECT
public:
    explicit Results(QWidget *parent = 0);
    Settings::simulationType getSimulationType();
    int getSimulationParameter();
    void drawFitnessOnIterationChart(double iteration, double best, double average, int graph);
    void drawNumberOnFitnessChart(vectorPairs numberOfIndivuals, int graph);
signals:
    void beginStepSimulationClicked();//sygnal parsowany dalej oznaczajacy przycisniecie przycisku startu symulacji klikanej
    void beginContinousSimulationClicked(); //sygnal parsowany dalej oznaczajacy przycisniecie przycisku startu symulacji ciaglej
    void continousSimulationPaused(); //sygnal do zatrzymania symulacji
    void reset(); //sygnal resetujacy
    void nextStep(); //sygnal do wykonania nastepnego kroka
public slots:
    void activateContinousButtons(); //slot uruchamiany przez mainWindow w momencie gdy controller uruchomi symulacje, trzeba zmienic przyciski dt. symulacji ciaglej
    void activateStepButtons(); //slot uruchamiany przez mainWindow w momencie gdy controller uruchomi symulacje, trzeba zmienic przyciski dt. symulacji krokowej
    void resetSimulationButtons(); //slot uruchamiany przez mainWIndow do resetowania przycisku rozpoczecia
private slots:
    void swapCharts();
    void swapBeginButtons();
private:
    /*Layout widgetu*/
    QGridLayout *widgetLayout;
    /*Grupa zawierające przyciski do wyboru symulacji */
    QGroupBox* simulationOptionsBox;
    /*Grupa zawierające przyciski do wyboru wykresu */
    QGroupBox* chartTypeBox;
    /*Przyciski od wyboru symulacji */
    QRadioButton* simulationOptionsButtons[2];
    /*Suwaki od wyboru parametrow symulacji */
    QSpinBox* simulationOptionsSpinBoxes[2];
    /*Przyciski od wyboru wykresu */
    QRadioButton* chartTypeButtons[2];
    /*Przycisk rozpoczynający symulacje klikana */
    QPushButton *beginButtonStep;
    /*Przycisk rozpoczynający symulacje ciaglla */
    QPushButton *beginButtonContinous;
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
