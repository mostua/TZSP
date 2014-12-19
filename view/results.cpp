#include "results.h"

Results::Results(QWidget *parent) :
    QWidget(parent)
{
    createWidgetItems();
    setWidgetLayout();
    createConnections();
}

void Results::createWidgetItems()
{
    widgetLayout = new QGridLayout();
    /* grupa zawierajace przyciski do wyboru typu symulacji */
    simulationOptionsBox = new QGroupBox(tr("Simulation Options"));
    simulationOptionsBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    simulationOptionsButtons[0] = new QRadioButton(tr("Step by step simulation"));
    simulationOptionsButtons[0]->setChecked(true);
    simulationOptionsButtons[1] = new QRadioButton(tr("Few steps by step simulation"));
    simulationOptionsButtons[2] = new QRadioButton(tr("Steps per second simulation"));
    /* suwalo dp wyboru parametrów krokowych symulacji */
    simulationOptionsSpinBoxes[0] = new QSpinBox();
    simulationOptionsSpinBoxes[1] = new QSpinBox();
    /* grupa zawierajaca przyciski do wyboru wykresu */
    chartTypeBox = new QGroupBox(tr("Chart Type"));
    chartTypeButtons[0] = new QRadioButton(tr("Fitness function value on iteration"));
    chartTypeButtons[0]->setChecked(true);
    chartTypeButtons[1] = new QRadioButton(tr("Number of indivuals on fitness function value"));
    beginButton = new QPushButton(tr("Begin"));
    resetButton = new QPushButton(tr("Reset"));
    resetButton->setEnabled(false);
    /* widget zawierajacy wykres */
    fitnessOnIterationChart = new QCustomPlot();
    fitnessOnIterationChart->yAxis->setLabel(tr("fitness"));
    fitnessOnIterationChart->xAxis->setLabel(tr("iteration"));
    numberOnFitnessChart = new QCustomPlot();
    numberOnFitnessChart->xAxis->setLabel(tr("fitness"));
    numberOnFitnessChart->yAxis->setLabel(tr("number"));
}

void Results::setWidgetLayout()
{
    /* glowny layout */
    setLayout(widgetLayout);
    /* layout grupy przyciskow wyboru symulacji */
    QGridLayout *gl;
    gl = new QGridLayout;
    gl->addWidget(simulationOptionsButtons[0],0,0);
    gl->addWidget(simulationOptionsButtons[1],1,0);
    gl->addWidget(simulationOptionsButtons[2],2,0);
    gl->addWidget(simulationOptionsSpinBoxes[0], 1,1);
    gl->addWidget(simulationOptionsSpinBoxes[1],2,1);
    simulationOptionsBox->setLayout(gl);
    chartTypeBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    /*layout grupy przyciskow wyboru wykresu */
    gl = new QGridLayout;
    gl->addWidget(chartTypeButtons[0]);
    gl->addWidget(chartTypeButtons[1]);
    chartTypeBox->setLayout(gl);
    /*layout prawej strony */
    QVBoxLayout *vb = new QVBoxLayout;
    vb->addWidget(simulationOptionsBox);
    vb->addWidget(chartTypeBox);
    vb->addWidget(beginButton);
    vb->addWidget(resetButton);
    /* w głównym layoutcie mamy 2, jeden od wykresu, drugi od przyciskow */
    widgetLayout->addLayout(vb, 0,1);
    fitnessOnIterationChart->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    fitnessOnIterationChart->setMinimumSize(400,300);
    numberOnFitnessChart->setMinimumSize(400,300);
    numberOnFitnessChart->setVisible(false);
    widgetLayout->addWidget(fitnessOnIterationChart, 0, 0);
    widgetLayout->addWidget(numberOnFitnessChart, 0, 0);
}

void Results::swapCharts()
{
    if(chartTypeButtons[0]->isChecked())
    {
        fitnessOnIterationChart->setVisible(true);
        numberOnFitnessChart->setVisible(false);
    }
    else
    {
        fitnessOnIterationChart->setVisible(false);
        numberOnFitnessChart->setVisible(true);
    }
}

void Results::createConnections()
{
    connect(chartTypeButtons[0], SIGNAL(toggled(bool)), this, SLOT(swapCharts()));
    connect(chartTypeButtons[1], SIGNAL(toggled(bool)), this, SLOT(swapCharts()));
    connect(beginButton, SIGNAL(clicked()), this, SIGNAL(beginSimulationClicked()));
}
