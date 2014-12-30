#include "mainwindow.h"

MainWindow::MainWindow(Model *model, QWidget *parent) : QMainWindow(parent)
{
    setMinimumSize(*(new QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));
    tabLayout = new QTabWidget(this);
    setCentralWidget(tabLayout);
    /* Creating items */
    createItemsForCentralWidget();
    /* Creating connections */
    createConnections();
}

MainWindow::~MainWindow()
{

}


void MainWindow::createItemsForCentralWidget()
{
    optionWidget = new Options;
    resultWidget = new Results;
    theBestListWidget = new TheBestList;
    tabLayout->addTab(optionWidget, tr("Options"));
    tabLayout->addTab(resultWidget, tr("Results"));
    tabLayout->addTab(theBestListWidget, tr("Best indivuals"));
}

void MainWindow::continousSimulationButtonPressed()
{
    try{
        Settings msg(optionWidget->getSquareSize(),optionWidget->getMi(), optionWidget->getAlpha(), optionWidget->getSelectionType(), optionWidget->getSquareType(), optionWidget->getReproductionType(), optionWidget->getMutationType(), resultWidget->getSimulationType(), resultWidget->getSimulationParameter());
        emit startContinousSimulation(msg);
    }catch(char const * e)
    {
        qDebug() << e;
    }
}

void MainWindow::stepSimulationButtonPressed()
{
    try{
        Settings msg(optionWidget->getSquareSize(),optionWidget->getMi(), optionWidget->getAlpha(), optionWidget->getSelectionType(), optionWidget->getSquareType(), optionWidget->getReproductionType(), optionWidget->getMutationType(), resultWidget->getSimulationType(), resultWidget->getSimulationParameter());
        emit startStepSimulation(msg);
    }catch(char const * e)
    {
        qDebug() << e;
    }
}

void MainWindow::createConnections()
{
    connect(resultWidget, SIGNAL(beginStepSimulationClicked()), this, SLOT(stepSimulationButtonPressed()));
    connect(resultWidget, SIGNAL(beginContinousSimulationClicked()), this, SLOT(continousSimulationButtonPressed()));
    connect(resultWidget, SIGNAL(reset()), this, SIGNAL(resetSimulation()));
    connect(this, SIGNAL(activateStepButtons()), resultWidget,  SLOT(activateStepButtons()));
    connect(this, SIGNAL(activateContinousButtons()), resultWidget, SLOT(activateContinousButtons()));
    connect(this, SIGNAL(resetSimulation()), resultWidget, SLOT(resetSimulationButtons()));
}

void MainWindow::drawFitnessGraph(double iteration, double best, double average, int graph)
{

}

void MainWindow::drawNumberofIndivuals(QVector<double> fitness, QVector<double> numberOfIndivuals, int graph)
{

}
