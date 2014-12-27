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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void drawNumberofIndivuals(QVector<double> fitness, QVector<double> numberOfIndivuals, int graph);
    void drawFitnessGraph(double iteration, double best, double average, int graph);

private slots:
   void continousSimulationButtonPressed();
   void stepSimulationButtonPressed();
signals:
    void startContinousSimulation(Settings settings);
    void startStepSimulation(Settings settings);
    void activateContinousButtons(); //slot uruchamiany przez mainWindow w momencie gdy controller uruchomi symulacje, trzeba zmienic przyciski dt. symulacji ciaglej
    void activateStepButtons(); //slot uruchamiany przez mainWindow w momencie gdy controller uruchomi symulacje, trzeba zmienic przyciski dt. symulacji krokowej
private:
    const int MAIN_WINDOW_HEIGHT = 600;
    const int MAIN_WINDOW_WIDTH = 800;
    QWidget *centralWidget;
    QHBoxLayout *centralWidgetLayout;
    Options *optionWidget;
    Results *resultWidget;
    TheBestList *theBestListWidget;
    /*tab layout*/
    QTabWidget *tabLayout;
    /*central layout elements*/
    QMenu *fileMenu;

    /*actions*/
    QAction *saveResults;
    /*logically devided create functions */
    void createItemsForCentralWidget();
    void createItemsForResultWidget();
    void createItemsForOptionLayout();
    void createItemsForGraphLayout();
    void createItemsForGroupBoxes();
    void createConnections();
};

#endif // MAINWINDOW_H
