#include "results.h"

Results::Results(QWidget *parent) :
    QWidget(parent)
{
    createWidgetItems();
    setWidgetLayout();
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
    /* widget zawierajacy wykres */
    graphWidget = new QCustomPlot();

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
    /* w głównym layoutcie mamy 2, jeden od wykresu, drugi od przyciskow */
    widgetLayout->addLayout(vb, 0,1);
    graphWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    graphWidget->setMinimumSize(400,300);
    widgetLayout->addWidget(graphWidget,0,0);
}
