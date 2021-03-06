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
        Settings msg(optionWidget->getSquareSize(),optionWidget->getMi(), optionWidget->getLambda(), optionWidget->getMinSigma(), optionWidget->getMaxSigma(), optionWidget->getSelectionType(), optionWidget->getSquareType(), optionWidget->getReproductionType(), optionWidget->getMutationType(), resultWidget->getSimulationType(), resultWidget->getSimulationParameter(), optionWidget->getAlgorithmType(), optionWidget->getCutPopulationValue(), optionWidget->getAddNewIndividualsInterval(), optionWidget->getAddNewIndividualsValue());
        emit startContinousSimulation(msg);
    }catch(char const * e)
    {
        qDebug() << e;
    }
}

void MainWindow::stepSimulationButtonPressed()
{
    try{
        Settings msg(optionWidget->getSquareSize(),optionWidget->getMi(), optionWidget->getLambda(), optionWidget->getMinSigma(), optionWidget->getMaxSigma(), optionWidget->getSelectionType(), optionWidget->getSquareType(), optionWidget->getReproductionType(), optionWidget->getMutationType(), resultWidget->getSimulationType(), resultWidget->getSimulationParameter(), optionWidget->getAlgorithmType(), optionWidget->getCutPopulationValue(), optionWidget->getAddNewIndividualsInterval(), optionWidget->getAddNewIndividualsValue());
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
    connect(resultWidget, SIGNAL(resetRequest()), this, SIGNAL(resetSimulation()));
    connect(this, SIGNAL(activateStepButtons()), resultWidget,  SLOT(activateStepButtons()));
    connect(this, SIGNAL(activateContinousButtons()), resultWidget, SLOT(activateContinousButtons()));
    connect(this, SIGNAL(resetSimulation()), resultWidget, SLOT(resetSimulationButtons()));
    connect(this, SIGNAL(simulationReseted()), resultWidget, SLOT(resetSimulationButtons()));
    connect(optionWidget, SIGNAL(squareSizeChanged(int)), theBestListWidget, SLOT(squareSizeChanged(int)));
    connect(this, SIGNAL(updateBest(vectorSquares)), theBestListWidget, SLOT(updateBest(vectorSquares)));
}

void MainWindow::drawFitnessGraph(double iteration, double best, double average, int graph)
{
    resultWidget->drawFitnessOnIterationChart(iteration,best,average,graph);
}

void MainWindow::drawNumberOfIndivuals(vectorPairs numberOfIndivuals, int graph)
{
    resultWidget->drawNumberOnFitnessChart(numberOfIndivuals, graph);
}

