#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  //  setMinimumSize(*(new QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));
    tabLayout = new QTabWidget(this);
    setCentralWidget(tabLayout);
    createItemsForCentralWidget();

    /*Creating actions*/
    saveResults  = new QAction(tr("Save"), this);

    /*Creating menus*/
//    fileMenu = menuBar()->addMenu(tr("File"));
//    fileMenu->addAction(saveResults);

    /*Creating connections */
    createConnections();
}

MainWindow::~MainWindow()
{

}


void MainWindow::createItemsForCentralWidget()
{
    optionWidget = new Options;
    resultWidget = new Results;
    tabLayout->addTab(optionWidget, tr("Options"));
    tabLayout->addTab(resultWidget, tr("Results"));
    squareResultTable = new QTableWidget(3,3);
    tabLayout->addTab(squareResultTable, tr("Best indivuals"));
}

void MainWindow::simulationButtonPressed()
{
    try{
        Settings msg(optionWidget->getSquareSize(),optionWidget->getMi(), optionWidget->getAlpha(), optionWidget->getSelectionType(), optionWidget->getSquareType(), optionWidget->getReproductionType(), optionWidget->getMutationType(), resultWidget->getSimulationType(), resultWidget->getSimulationParameter());
        emit startSimulation(msg);
    }catch(char const * e)
    {
        qDebug() << e;
    }
}

void MainWindow::createConnections()
{
    connect(resultWidget, SIGNAL(beginSimulationClicked()), this, SLOT(simulationButtonPressed()));
}

void MainWindow::drawFitnessGraph(double iteration, double best, double average, int graph)
{

}

void MainWindow::drawNumberofIndivuals(QVector<double> fitness, QVector<double> numberOfIndivuals, int graph)
{

}
