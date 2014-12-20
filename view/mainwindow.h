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
#include <libraries/qcustomplot.h>
#include <QDebug>
#include "options.h"
#include "results.h"
#include "model/settings.h"

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
   void simulationButtonPressed();

signals:
    void startSimulation(Settings settings);

private:
    const int MAIN_WINDOW_HEIGHT = 600;
    const int MAIN_WINDOW_WIDTH = 800;
    QWidget *centralWidget;
    QHBoxLayout *centralWidgetLayout;
    Options *optionWidget;
    Results *resultWidget;
    /*tab layout*/
    QTabWidget *tabLayout;
    /*central layout elements*/
    QMenu *fileMenu;
    /*tab individuals */
    QTableWidget *squareResultTable;
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
