#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)//,
    //ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
  //  setMinimumSize(*(new QSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT)));
    tabLayout = new QTabWidget(this);
    setCentralWidget(tabLayout);
    createItemsForCentralWidget();

    /*Creating actions*/
    saveResults  = new QAction(tr("Save"), this);

    /*Creating menus*/
/*    fileMenu = menuBar()->addMenu(tr("File"));
    fileMenu->addAction(saveResults);*/

    /*Creating connections */
    createConnections();
}

MainWindow::~MainWindow()
{
    //delete ui;
}


void MainWindow::createItemsForCentralWidget()
{
    optionWidget = new QWidget();
    resultWidget = new QWidget();
    tabLayout->addTab(optionWidget, tr("Options"));
    tabLayout->addTab(resultWidget, tr("Results"));
    //optionWidget->setMinimumSize(*(new QSize(MAIN_WINDOW_WIDTH/2, MAIN_WINDOW_HEIGHT)));
    //resultWidget->setMinimumSize(*(new QSize(MAIN_WINDOW_WIDTH/2, MAIN_WINDOW_HEIGHT)));
    optionLayout = new QGridLayout();
    optionWidget->setLayout(optionLayout);
    createItemsForOptionLayout();
    createItemsForResultWidget();
    squareResultTable = new QTableWidget(3,3);
    tabLayout->addTab(squareResultTable, tr("best indivuals"));
}

void MainWindow::createItemsForOptionLayout()
{
    squareSizeText = new QLabel(tr("Square side size:"));
    optionLayout->addWidget(squareSizeText, 0,0);

    squareSizeBox = new QSpinBox();
    squareSizeBox->setRange(3,MAX_SQUARE_SIZE);
    squareSizeBox->setSingleStep(1);
    squareSizeBox->setValue(3);
    optionLayout->addWidget(squareSizeBox, 0,1);

    squareTypeBox = new QGroupBox(tr("Square Type Box"));
    squareTypeButtons[0] = new QRadioButton(tr("Diagonals are important"));
    squareTypeButtons[1] = new QRadioButton(tr("Diagonals are not important"));
    QVBoxLayout *vb = new QVBoxLayout;
    vb->addWidget(squareTypeButtons[0]);
    vb->addWidget(squareTypeButtons[1]);
    squareTypeBox->setLayout(vb);
    squareTypeButtons[0]->setChecked(true);
    optionLayout->addWidget(squareTypeBox,1,0);

    algorithmStrategyBox  = new QGroupBox(tr("Algorithm Strategy"));
    algorithmStrategyButtons[0] = new QRadioButton(QString("%1 + %2").arg(QChar(0xb1, 0x03),QChar(0xbc, 0x03)));
    algorithmStrategyButtons[1] = new QRadioButton(QString("(%1, %2)").arg(QChar(0xb1, 0x03),QChar(0xbc, 0x03)));
    vb = new QVBoxLayout;
    vb->addWidget(algorithmStrategyButtons[0]);
    vb->addWidget(algorithmStrategyButtons[1]);
    algorithmStrategyBox->setLayout(vb);
    algorithmStrategyButtons[0]->setChecked(true);
    algorithmStrategyBox->setLayout(vb);
    optionLayout->addWidget(algorithmStrategyBox, 2,0);


    selectionTypeBox  = new QGroupBox(tr("Selection Type"));
    selectionTypeButtons[0] = new QRadioButton(tr("Ranking"));
    selectionTypeButtons[1] = new QRadioButton(tr("Random"));
    selectionTypeButtons[2] = new QRadioButton(tr("Propotional"));
    vb = new QVBoxLayout;
    vb->addWidget(selectionTypeButtons[0]);
    vb->addWidget(selectionTypeButtons[1]);
    vb->addWidget(selectionTypeButtons[2]);
    selectionTypeButtons[0]->setChecked(true);
    selectionTypeBox->setLayout(vb);
    optionLayout->addWidget(selectionTypeBox, 3,0);

    reproductionTypeBox = new QGroupBox(tr("Reproduction Type"));
    reproductionTypeButtons[0] = new QRadioButton(tr("Saving diagonals"));
    reproductionTypeButtons[1] = new QRadioButton(tr("Saving columns"));
    reproductionTypeButtons[2] = new QRadioButton(tr("Saving rows"));
    vb = new QVBoxLayout;
    vb->addWidget(reproductionTypeButtons[0]);
    vb->addWidget(reproductionTypeButtons[1]);
    vb->addWidget(reproductionTypeButtons[2]);
    reproductionTypeButtons[0]->setChecked(true);
    reproductionTypeBox->setLayout(vb);
    optionLayout->addWidget(reproductionTypeBox, 1,1);

    mutationTypeBox = new QGroupBox(tr("Mutation Type"));
    mutationTypeButtons[0] = new QRadioButton(tr("Swap random fields"));
    mutationTypeButtons[1] = new QRadioButton(tr("Swap row/column"));
    vb = new QVBoxLayout;
    vb->addWidget(mutationTypeButtons[0]);
    vb->addWidget(mutationTypeButtons[1]);
    mutationTypeButtons[0]->setChecked(true);
    mutationTypeBox->setLayout(vb);
    optionLayout->addWidget(mutationTypeBox, 2,1);

    beginButton = new QPushButton(tr("Begin"));
    optionLayout->addWidget(beginButton,2,1);

    //substitution
    chartSubstitue = new QTextEdit();
    optionLayout->addWidget(chartSubstitue, 3,1);
    //endsubstitution
}

void MainWindow::createItemsForResultWidget()
{
    graphLayout = new QGridLayout();
    resultWidget->setLayout(graphLayout);

    simulationOptionsBox = new QGroupBox(tr("Simulation Options"));
    simulationOptionsBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    simulationOptionsButtons[0] = new QRadioButton(tr("Step by step simulation"));
    simulationOptionsButtons[0]->setChecked(true);
    simulationOptionsButtons[1] = new QRadioButton(tr("Few steps by step simulation"));
    simulationOptionsButtons[2] = new QRadioButton(tr("Steps per second simulation"));
    simulationOptionsSpinBoxes[0] = new QSpinBox();
    simulationOptionsSpinBoxes[1] = new QSpinBox();
    QGridLayout *gl = new QGridLayout;
    gl->addWidget(simulationOptionsButtons[0],0,0);
    gl->addWidget(simulationOptionsButtons[1],1,0);
    gl->addWidget(simulationOptionsButtons[2],2,0);
    gl->addWidget(simulationOptionsSpinBoxes[0], 1,1);
    gl->addWidget(simulationOptionsSpinBoxes[1],2,1);
    simulationOptionsBox->setLayout(gl);

    chartTypeBox = new QGroupBox(tr("Chart Type"));
    chartTypeBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    chartTypeButtons[0] = new QRadioButton(tr("Fitness function value on iteration"));
    chartTypeButtons[0]->setChecked(true);
    chartTypeButtons[1] = new QRadioButton(tr("Number of indivuals on fitness function value"));
    gl = new QGridLayout;
    gl->addWidget(chartTypeButtons[0]);
    gl->addWidget(chartTypeButtons[1]);
    chartTypeBox->setLayout(gl);

    QVBoxLayout *vb = new QVBoxLayout;
    vb->addWidget(simulationOptionsBox);
    vb->addWidget(chartTypeBox);
    vb->addWidget(beginButton);
    graphLayout->addLayout(vb, 0,1);

    graphWidget = new QCustomPlot();
    graphWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    graphLayout->addWidget(graphWidget,0,0);
}

void MainWindow::createConnections()
{
    connect(beginButton, SIGNAL(clicked()), this, SLOT(simulationButtonPressed()));
}

void MainWindow::addIterationToFitnessFunction(double iteration, double best, double average, int graph)
{
    //graphWidget
}

void MainWindow::simulationButtonPressed()
{
    emit startSimulation(squareSizeBox->value());
}
