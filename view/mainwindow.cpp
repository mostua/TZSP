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
    /* Sygnaly wywolywane po przycisnieciu przycisku rozpoczecia symulacji */
    connect(resultWidget, SIGNAL(beginStepSimulationClicked()), this, SLOT(stepSimulationButtonPressed()));
    connect(resultWidget, SIGNAL(beginContinousSimulationClicked()), this, SLOT(continousSimulationButtonPressed()));
    /* Slot odpowiadajacy za zmiane przycisku */
    connect(this, SIGNAL(activateStepButtons()), resultWidget,  SLOT(activateStepButtons()));
    connect(this, SIGNAL(activateContinousButtons()), resultWidget, SLOT(activateContinousButtons()));
}

void MainWindow::drawFitnessGraph(double iteration, double best, double average, int graph)
{

}

void MainWindow::drawNumberofIndivuals(QVector<double> fitness, QVector<double> numberOfIndivuals, int graph)
{

}
