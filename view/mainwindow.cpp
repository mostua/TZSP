#include "mainwindow.h"
#include "ui_mainwindow.h"
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
    graphLayout = new QGridLayout();
    optionWidget->setLayout(optionLayout);
    resultWidget->setLayout(graphLayout);
    createItemsForGraphLayout();
    createItemsForOptionLayout();
}

void MainWindow::createItemsForOptionLayout()
{
    QList<QString> boxNames;
    boxNames.push_back(tr("Square Type Box"));
    boxNames.push_back(tr("Algorithm Strategy"));
    boxNames.push_back(tr("Selection Type"));
    boxNames.push_back(tr("Reproduction Type"));
    boxNames.push_back(tr("Mutation Type"));
    boxNames.push_back(tr("Chart Type"));

    boxList = new QList<QGroupBox *>();

    int i = 0;
    for(QList<QString>::iterator it = boxNames.begin(); it!=boxNames.end(); it++, ++i)
    {
            boxList->push_back(new QGroupBox(*it));
    }
    squareSizeText = new QLabel(tr("Square side size:"));
    squareSizeBox = new QSpinBox();
    squareSizeBox->setRange(3,MAX_SQUARE_SIZE);
    squareSizeBox->setSingleStep(1);
    squareSizeBox->setValue(3);

    optionLayout->addWidget(squareSizeText, 0,0);
    optionLayout->addWidget(squareSizeBox, 0,1);
    QList<QGroupBox *>::iterator it = boxList->begin();
    optionLayout->addWidget(*it++, 1,0);
    optionLayout->addWidget(*it++, 2,0);
    optionLayout->addWidget(*it++, 3,0);
    optionLayout->addWidget(*it++, 4,0);
    optionLayout->addWidget(*it++, 5,0);
    optionLayout->addWidget(*it++, 6,0);
    beginButton = new QPushButton(tr("Begin"));
    optionLayout->addWidget(beginButton,2,1);
    squareResultTable = new QTableWidget(3,3);
    optionLayout->addWidget(squareResultTable, 3,1);

    //substitution
    chartSubstitue = new QTextEdit();
    optionLayout->addWidget(chartSubstitue, 4,1);
    //endsubstitution
    simulationTypeGroup = new QGroupBox(tr("Simulation Options"));
    optionLayout->addWidget(simulationTypeGroup, 1,1);
    createItemsForGroupBoxes();
}

void MainWindow::createItemsForGroupBoxes()
{
    QString buttonNames[6][3];

    buttonNames[0][0] = tr("Diagonals are imporant");
    buttonNames[0][1] = tr("Diagonals are not imporant");
    buttonNames[1][0] = tr("labda + mi");
    buttonNames[1][1] = tr("(labda,mi)");
    buttonNames[2][0] = tr("Ranking");
    buttonNames[2][1] = tr("Random");
    buttonNames[2][2] = tr("Propotional");
    buttonNames[3][0] = tr("Saving Diagonals");
    buttonNames[3][1] = tr("Saving Columns");
    buttonNames[3][2] = tr("Saving Raws");
    buttonNames[4][0] = tr("Swap random fields");
    buttonNames[4][1] = tr("Swap raw/column");
    buttonNames[5][0] = tr("Fitness function value on iteration");
    buttonNames[5][1] = tr("Number of indivuals on fitness function value");

    boxLayouts = new QList<QVBoxLayout *>();
    buttonList = new QList<QRadioButton *>();

    for(int i =0 ; i<6; i++)
    {
        boxLayouts->push_back(new QVBoxLayout(boxList->at(i)));
        for(int j =0; j<3; j++)
        {
            if(buttonNames[i][j]==NULL)
                continue;
            boxLayouts->at(i)->addWidget(new QRadioButton(buttonNames[i][j]));
        }
    }

    simulationTypeLayout = new QGridLayout(simulationTypeGroup);

    simulationTypeButtonList = new QList<QRadioButton *>();
    simulationTypeBoxList = new QList<QSpinBox *>();
    simulationTypeButtonList->push_back(new QRadioButton(tr("Step by step simulation")));
    simulationTypeButtonList->push_back(new QRadioButton(tr("Few steps by step simulation")));
    simulationTypeButtonList->push_back(new QRadioButton(tr("Step per second simulation")));
    simulationTypeBoxList->push_back(new QSpinBox());
    simulationTypeBoxList->at(0)->setRange(1,10000);
    simulationTypeBoxList->at(0)->setSingleStep(1);
    simulationTypeBoxList->push_back(new QSpinBox());
    simulationTypeBoxList->at(1)->setRange(1,60);
    simulationTypeBoxList->at(1)->setSingleStep(1);
    simulationTypeLayout->addWidget(simulationTypeButtonList->at(0), 0,0);
    simulationTypeLayout->addWidget(simulationTypeButtonList->at(1), 1,0);
    simulationTypeLayout->addWidget(simulationTypeButtonList->at(2), 2,0);
    simulationTypeLayout->addWidget(simulationTypeBoxList->at(0), 1,1);
    simulationTypeLayout->addWidget(simulationTypeBoxList->at(1), 2,1);

}

void MainWindow::createItemsForGraphLayout()
{
    graphWidget = new QCustomPlot();
    graphLayout->addWidget(graphWidget);
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    graphWidget->addGraph();
    graphWidget->graph(0)->setData(x, y);
    // give the axes some labels:
    graphWidget->xAxis->setLabel("x");
    graphWidget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    graphWidget->xAxis->setRange(-1, 1);
    graphWidget->yAxis->setRange(0, 1);
    graphWidget->replot();
}

void MainWindow::createConnections()
{
    connect(beginButton, SIGNAL(clicked()), this, SLOT(simulationButtonPressed()));

}

void MainWindow::addIteration(QString value)
{
    chartSubstitue->append("\n" + value);
}

void MainWindow::simulationButtonPressed()
{
    emit startSimulation(squareSizeBox->value());
}
