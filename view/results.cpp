#include "results.h"

Results::Results(QWidget *parent) :
    QWidget(parent)
{
    createWidgetItems();
    setWidgetLayout();
    createConnections();
}

Settings::simulationType Results::getSimulationType()
{
    if(simulationOptionsButtons[0]->isChecked())
        return Settings::stepsByStep;
    if(simulationOptionsButtons[1]->isChecked())
        return Settings::fewStepsPerSecond;
    throw "nothing is checked in simulation section";
}

int Results::getSimulationParameter()
{
    Settings::simulationType type = getSimulationType();
    int result;
    if(type == Settings::stepsByStep)
    {
        result = simulationOptionsSpinBoxes[0]->value();
        if(result < MIN_STEPS_VALUE || result > MAX_STEPS_VALUE)
            throw "steps value out of range";
    }
    else
    {
        result = simulationOptionsSpinBoxes[1]->value();
        if(result < MIN_STEPS_PER_SECOND || result > MAX_STEPS_PER_SECOND)
            throw "steps value out of range";
    }
    return result;

}

void Results::resetSimulationButtons()
{
    beginButtonContinous->setText(tr("Begin continous simulation"));
    beginButtonStep->setText(tr("Begin step simulation"));
    resetButton->setEnabled(false);
    fitnessOnIterationChart->clearGraphs();
}

void Results::activateContinousButtons()
{
    beginButtonContinous->setText(tr("Pause"));
    resetButton->setEnabled(true);
}

void Results::activateStepButtons()
{
    beginButtonStep->setText(tr("Next step"));
    resetButton->setEnabled(true);
}

void Results::createWidgetItems()
{
    widgetLayout = new QGridLayout();
    /* grupa zawierajace przyciski do wyboru typu symulacji */
    simulationOptionsBox = new QGroupBox(tr("Simulation Options"));
    simulationOptionsBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
//    simulationOptionsButtons[0] = new QRadioButton(tr("Step by step simulation"));
//    simulationOptionsButtons[0]->setChecked(true);
    simulationOptionsButtons[0] = new QRadioButton(tr("Few steps by step simulation"));
    simulationOptionsButtons[0]->setChecked(true);
    simulationOptionsButtons[1] = new QRadioButton(tr("Steps per second simulation"));
    /* suwaki do wyboru parametrów krokowych symulacji */
    simulationOptionsSpinBoxes[0] = new QSpinBox();
    simulationOptionsSpinBoxes[0]->setRange(MIN_STEPS_VALUE, MAX_STEPS_VALUE);
    simulationOptionsSpinBoxes[0]->setValue(MIN_STEPS_VALUE);
    simulationOptionsSpinBoxes[1] = new QSpinBox();
    simulationOptionsSpinBoxes[1]->setRange(MIN_STEPS_PER_SECOND, MAX_STEPS_PER_SECOND);
    simulationOptionsSpinBoxes[1]->setValue(MIN_STEPS_PER_SECOND);
    /* grupa zawierajaca przyciski do wyboru wykresu */
    chartTypeBox = new QGroupBox(tr("Chart Type"));
    chartTypeButtons[0] = new QRadioButton(tr("Fitness function value on iteration"));
    chartTypeButtons[0]->setChecked(true);
    chartTypeButtons[1] = new QRadioButton(tr("Number of indivuals on fitness function value"));
    beginButtonStep = new QPushButton(tr("Begin step simulation"));
    beginButtonContinous = new QPushButton(tr("Begin continous simulation"));
    resetButton = new QPushButton(tr("Reset"));
    resetButton->setEnabled(false);
    /* widget zawierajacy wykres */
    fitnessOnIterationChart = new QCustomPlot();
    fitnessOnIterationChart->yAxis->setLabel(tr("fitness"));
    fitnessOnIterationChart->xAxis->setLabel(tr("iteration"));
    fitnessOnIterationChart->xAxis->setRange(0,10);
    fitnessOnIterationChart->yAxis->setRange(0,9);
    fitnessOnIterationChart->legend->setVisible(true);
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
    gl->addWidget(simulationOptionsSpinBoxes[0],0,1);
    gl->addWidget(simulationOptionsSpinBoxes[1],1,1);
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
    QGridLayout *beginsButtons = new QGridLayout;
    beginsButtons->addWidget(beginButtonContinous,0,0);
    beginButtonContinous->setVisible(false);
    beginsButtons->addWidget(beginButtonStep,0,0);
    vb->addLayout(beginsButtons);
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

void Results::swapBeginButtons()
{
    if(simulationOptionsButtons[0]->isChecked())
    {
        beginButtonStep->setVisible(true);
        beginButtonContinous->setVisible(false);
    }
    else
    {
        beginButtonStep->setVisible(false);
        beginButtonContinous->setVisible(true);
    }
}

void Results::createConnections()
{
    connect(chartTypeButtons[0], SIGNAL(toggled(bool)), this, SLOT(swapCharts()));
    connect(chartTypeButtons[1], SIGNAL(toggled(bool)), this, SLOT(swapCharts()));
    connect(simulationOptionsButtons[0], SIGNAL(toggled(bool)), this, SLOT(swapBeginButtons()));
    connect(simulationOptionsButtons[1], SIGNAL(toggled(bool)), this, SLOT(swapBeginButtons()));
    connect(beginButtonContinous, SIGNAL(clicked()), this, SIGNAL(beginContinousSimulationClicked()));
    connect(beginButtonStep, SIGNAL(clicked()), this, SIGNAL(beginStepSimulationClicked()));
    connect(resetButton, SIGNAL(clicked()), this, SIGNAL(reset()));
}

void Results::drawFitnessOnIterationChart(double iteration, double best, double average, int graph)
{
    /*making the neccesary amount of graphs*/
    if(2*graph > fitnessOnIterationChart->graphCount() - 2)
    {
        /*adding nessecary amount of graphs*/
        for(int i = 2*graph - fitnessOnIterationChart->graphCount() + 2; i > 0; i=i-2)
        {
            fitnessOnIterationChart->addGraph();
            fitnessOnIterationChart->graph()->setName(tr("best " + graph));
            fitnessOnIterationChart->graph()->setPen(QPen(QColor(255, 0, 0)));
            fitnessOnIterationChart->addGraph();
            fitnessOnIterationChart->graph()->setName(tr("average " + graph));
            fitnessOnIterationChart->graph()->setPen(QPen(QColor(255, 255, 0)));
        }
    }

    /*checking ranges of graph, if too small we expand it*/
    if(fitnessOnIterationChart->yAxis->range().size() < best || fitnessOnIterationChart->yAxis->range().size() < average)
        fitnessOnIterationChart->yAxis->setRange(0.0, average + 1.0);
    if(fitnessOnIterationChart->xAxis->range().size() < iteration)
        fitnessOnIterationChart->xAxis->scaleRange(2.0,1.0);

    /*adding new data to graph*/
    fitnessOnIterationChart->graph(graph)->addData(iteration, best);
    fitnessOnIterationChart->graph(graph+1)->addData(iteration,average);
    fitnessOnIterationChart->replot();
}

void Results::drawNumberOnFitnessChart(vectorPairs numberOfIndivuals, int graph)
{

}
