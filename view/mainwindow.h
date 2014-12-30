#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QMap>
#include <QString>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDebug>
#include "options.h"
#include "results.h"
#include "thebestlist.h"
#include "../model/settings.h"
#include "../libraries/qcustomplot.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Model * model, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void drawNumberofIndivuals(QVector<double> fitness, QVector<double> numberOfIndivuals, int graph);
    void drawFitnessGraph(double iteration, double best, double average, int graph);
private slots:
    /*!
     * \brief continousSimulationButtonPressed slot obslugujacy widgety, wyciaga z nich informacje i nadaje sygnal rozpoczecia symulacji ciaglej
     */
    void continousSimulationButtonPressed();
    /*!
     * \brief stepSimulationButtonPressed slot obslugujacy widgety, wyciaga z nich informacje i nadaje sygnal rozpoczecia symulacji krokowej
     */
    void stepSimulationButtonPressed();

signals:
    /*!
     * \brief startContinousSimulation sygnał wyzwalany w momemncia przycisniecia rozpoczecia symulacji ciaglej
     * \param settings parametr zawierający informacje o symulacji
     */
    void startContinousSimulation(Settings settings);
    /*!
     * \brief startStepSimulation sygnał wyzwalany w momemncia przycisniecia rozpoczecia symulacji krokowej
     * \param settings parametr zawierający informacje o symulacji
     */
    void startStepSimulation(Settings settings);
    /*!
     * \brief activateContinousButtons sygnał uruchamiany przez mainWindow w momencie gdy controller uruchomi symulacje, trzeba zmienic przyciski dt. symulacji ciaglej
     */
    void activateContinousButtons();
    /*!
     * \brief activateStepButtons sygnał uruchamiany przez mainWindow w momencie gdy controller uruchomi symulacje, trzeba zmienic przyciski dt. symulacji krokowej
     */
    void activateStepButtons();
    /*!
     * \brief resetSimulation sygnał uruchamiany przez widget i przepychany do controllera w momencie resetowania symulacji
     */
    void resetSimulation();
    /*!
     * \brief simulationReseted sygnał uruchamiany przez controller i przepychany do widzetu result
     */
    void simulationReseted();
private:
    /*!
     * \brief MAIN_WINDOW_HEIGHT  domyślna wysokość okna
     */
    const int MAIN_WINDOW_HEIGHT = 600;
    /*!
     * \brief MAIN_WINDOW_WIDTH domyślna szerokość okna
     */
    const int MAIN_WINDOW_WIDTH = 800;
    /*!
     * \brief centralWidget widget w przechowuajcy zakładki
     */
    QWidget *centralWidget;
    /*!
     * \brief centralWidgetLayout layout widżetu przechowującego zakładki
     */
    QHBoxLayout *centralWidgetLayout;
    /*!
     * \brief optionWidget widżet z opcjami dotyczącymi symulacji
     */
    Options *optionWidget;
    /*!
     * \brief resultWidget widżet z wykresem i przyciskami dotyczącymi symulacji
     */
    Results *resultWidget;
    /*!
     * \brief theBestListWidget widżet dostępu do najlepszych kwadratów
     */
    TheBestList *theBestListWidget;
    /*!
     * \brief tabLayout layout zakładkowy
     */
    QTabWidget *tabLayout;
    /*logically devided create functions */
    void createItemsForCentralWidget();
    void createItemsForResultWidget();
    void createItemsForOptionLayout();
    void createItemsForGraphLayout();
    void createItemsForGroupBoxes();
    void createConnections();
};

#endif // MAINWINDOW_H
