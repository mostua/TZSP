#include "options.h"

Options::Options(QWidget *parent) :
    QWidget(parent)
{
    lambda = QChar(0xbb, 0x03);
    mi = QChar(0xbc, 0x03);
    createWidgetItems();
    setWidgetLayout();
    createConnections();
}

void Options::createWidgetItems()
{
    /*Suwak do wyboru rozmiaru kwadratu*/
    squareSizeText = new QLabel(tr("Square side size:"));
    squareSizeBox = new QSpinBox;
    squareSizeBox->setRange(MIN_SQUARE_SIZE,MAX_SQUARE_SIZE);
    squareSizeBox->setSingleStep(1);
    squareSizeBox->setValue(MIN_SQUARE_SIZE);
    /*Suwak do wyboru wielkosci parametru alpha */
    lambdaSizeText = new QLabel(QString(lambda) + tr(" parameter value:"));
    lambdaSizeBox = new QSpinBox;
    lambdaSizeBox->setRange(MIN_LAMBDA_VALUE,MAX_LAMBDA_VALUE);
    lambdaSizeBox->setSingleStep(1);
    lambdaSizeBox->setValue(DEFAULT_LAMBDA_VALUE);
    /*Suwak do wyboru wielkosci parametru mi*/
    miSizeText = new QLabel(QString(mi) + tr(" parameter value:"));
    miSizeBox = new QSpinBox;
    miSizeBox->setRange(MIN_MI_VALUE,MAX_MI_VALUE);
    miSizeBox->setSingleStep(1);
    miSizeBox->setValue(DEFAULT_MI_VALUE);
    /*Slider do wyboru minimum prawd */
    minPropabilityText = new QLabel(tr("Min phi value:"));
    minPropabilitySlider = new QSlider(Qt::Horizontal);
    minPropabilityValue = new QLabel("0.00");
    minPropabilityValue->setMinimumWidth(30);
    minPropabilitySlider->setMinimum(0);
    minPropabilitySlider->setMaximum(100);
    /*Slider do wyboru max prawd */
    maxPropabilityText = new QLabel(tr("Max phi value:"));
    maxPropabilitySlider = new QSlider(Qt::Horizontal);
    maxPropabilityValue = new QLabel("0.00");
    maxPropabilityValue->setMinimumWidth(30);
    maxPropabilitySlider->setMinimum(0);
    maxPropabilitySlider->setMaximum(100);
    /*Slideer do wyboru maximum prawd */
    /*Grupa przyciskow do wyboru magicznego kwadratu */
    squareTypeBox = new QGroupBox(tr("Square Type"));
    squareTypeButtons[0] = new QRadioButton(tr("Diagonals are important"));
    squareTypeButtons[1] = new QRadioButton(tr("Diagonals are not important"));
    squareTypeButtons[0]->setChecked(true);

    /*Grupa przyciskow do wyboru typu strategii */
    algorithmStrategyBox  = new QGroupBox(tr("Algorithm Strategy"));
    algorithmStrategyButtons[0] = new QRadioButton(QString("%1 + %2").arg(lambda, mi));
    algorithmStrategyButtons[1] = new QRadioButton(QString("(%1, %2)").arg(lambda, mi));
    //algorytm (lambda, mi) nie zakodowany w 100%
    algorithmStrategyButtons[1]->setDisabled(true);
    algorithmStrategyButtons[0]->setChecked(true);

    /*Grupa przyciskow do wyboru osobników do rozmnażania */
    selectionTypeBox  = new QGroupBox(tr("Selection Type"));
    selectionTypeButtons[0] = new QRadioButton(tr("Ranking"));
    selectionTypeButtons[1] = new QRadioButton(tr("Rulete"));
    selectionTypeButtons[2] = new QRadioButton(tr("Best"));
    selectionTypeButtons[0]->setChecked(true);

    /*Grupa przycisków do wyboru rodzaju reprodukcji */
    reproductionTypeBox = new QGroupBox(tr("Reproduction Type"));
    reproductionTypeButtons[0] = new QRadioButton(tr("Saving diagonals"));
    reproductionTypeButtons[1] = new QRadioButton(tr("Saving columns"));
    reproductionTypeButtons[2] = new QRadioButton(tr("Saving rows"));
    reproductionTypeButtons[0]->setChecked(true);

    /*Grupa przycisków do wyboru rodzaju mutacji */
    mutationTypeBox = new QGroupBox(tr("Mutation Type"));
    mutationTypeButtons[0] = new QRadioButton(tr("Swap random fields"));
    mutationTypeButtons[1] = new QRadioButton(tr("Swap row/column"));
    mutationTypeButtons[0]->setChecked(true);
    /*Grupa przycisków do wyboru optymalizacji */
    optimalizationBox = new QGroupBox(tr("Optimalizations"));
    cutPopulationCheckBox = new QCheckBox("Limit population to ");
    cutPopulationValue = new QSpinBox;
    cutPopulationValue->setRange(DEFAULT_MI_VALUE+DEFAULT_LAMBDA_VALUE, MAX_MI_VALUE + MAX_LAMBDA_VALUE);
    addRandomIndividualsCheckBox = new QCheckBox("Add new random individuals if not succes.");
    addRandomIndividualsHowManyText = new QLabel("How many:");
    addRandomIndividualsHowManyValue = new QSpinBox;
    addRandomIndividualsHowManyValue->setRange(MIN_LAMBDA_VALUE, MAX_LAMBDA_VALUE/4);
    addRandomIndividualsHowManyValue->setValue(DEFAULT_LAMBDA_VALUE);
    addRandomIndividualsHowFrequentText = new QLabel("How frequent");
    addRandomIndividualsHowFrequentValue = new QSpinBox;
    addRandomIndividualsHowFrequentValue->setRange(20,1000);
    addRandomIndividualsHowFrequentValue->setValue(100);
    addRandomIndividualsHowFrequentValue->setSingleStep(20);
}

void Options::createConnections()
{
    connect(squareSizeBox, SIGNAL(valueChanged(int)), this, SIGNAL(squareSizeChanged(int)));
    connect(minPropabilitySlider, SIGNAL(valueChanged(int)), this, SLOT(setMinPropabilityValue(int)));
    connect(maxPropabilitySlider, SIGNAL(valueChanged(int)), this, SLOT(setMaxPropabilityValue(int)));
    connect(miSizeBox, SIGNAL(valueChanged(int)), this, SLOT(setMinimumCut(int)));
    connect(lambdaSizeBox, SIGNAL(valueChanged(int)), this, SLOT(setMinimumCut(int)));
}


void Options::setWidgetLayout()
{
    /*Głowny layout */
    optionLayout = new QGridLayout();
    setLayout(optionLayout);
    /*Na górze przyciski dotyczace rozmiaru kwadratu */
    optionLayout->addWidget(squareSizeText, 0, 0);
    optionLayout->addWidget(squareSizeBox, 0, 1, 1, 2);
    /*Niżej przyciski dotyczace parametrów alpha i mi */
    optionLayout->addWidget(lambdaSizeText, 1, 0);
    optionLayout->addWidget(lambdaSizeBox, 1, 1, 1, 2);
    optionLayout->addWidget(miSizeText, 2, 0);
    optionLayout->addWidget(miSizeBox, 2, 1, 1, 2);
    /* Wybór prawdopodobieństwa */
    optionLayout->addWidget(minPropabilityText, 3, 0);
    optionLayout->addWidget(minPropabilitySlider, 3, 1);
    optionLayout->addWidget(minPropabilityValue, 3, 2);
    optionLayout->addWidget(maxPropabilityText, 4, 0);
    optionLayout->addWidget(maxPropabilitySlider, 4, 1);
    optionLayout->addWidget(maxPropabilityValue, 4, 2);
    /*Layout w grupie od rodzaju kwadratu */
    QVBoxLayout *vb;
    QHBoxLayout *hb;
    QWidget *emptyWidget;
    vb = new QVBoxLayout;
    vb->addWidget(squareTypeButtons[0]);
    vb->addWidget(squareTypeButtons[1]);
    squareTypeBox->setLayout(vb);
    optionLayout->addWidget(squareTypeBox,5,0);
    /*Layout w grupie od rodzaju strategi */
    vb = new QVBoxLayout;
    vb->addWidget(algorithmStrategyButtons[0]);
    vb->addWidget(algorithmStrategyButtons[1]);
    algorithmStrategyBox->setLayout(vb);
    optionLayout->addWidget(algorithmStrategyBox, 6, 0);
    /*Layout w grupie od rodzaju selekcji */
    vb = new QVBoxLayout;
    vb->addWidget(selectionTypeButtons[0]);
    vb->addWidget(selectionTypeButtons[1]);
    vb->addWidget(selectionTypeButtons[2]);
    selectionTypeBox->setLayout(vb);
    optionLayout->addWidget(selectionTypeBox, 7, 0);
    /*Layout w grupie od rodzaju reprodukcji */
    vb = new QVBoxLayout;
    vb->addWidget(reproductionTypeButtons[0]);
    vb->addWidget(reproductionTypeButtons[1]);
    vb->addWidget(reproductionTypeButtons[2]);
    reproductionTypeBox->setLayout(vb);
    optionLayout->addWidget(reproductionTypeBox, 5, 1, 1, 2);
    /*Layout w grupie od rodzaju mutacji*/
    vb = new QVBoxLayout;
    vb->addWidget(mutationTypeButtons[0]);
    vb->addWidget(mutationTypeButtons[1]);
    mutationTypeBox->setLayout(vb);
    optionLayout->addWidget(mutationTypeBox, 6, 1, 1, 2);
    /*Laypit w grupie od rodzaju optymalizacji */
    vb = new QVBoxLayout;
    hb = new QHBoxLayout;
    hb->addWidget(cutPopulationCheckBox);
    hb->addWidget(cutPopulationValue);
    emptyWidget = new QWidget;
    emptyWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    hb->addWidget(emptyWidget);
    vb->addLayout(hb);
    hb = new QHBoxLayout;
    hb->addWidget(addRandomIndividualsCheckBox);
    hb->addWidget(addRandomIndividualsHowFrequentText);
    hb->addWidget(addRandomIndividualsHowFrequentValue);
    hb->addWidget(addRandomIndividualsHowManyText);
    hb->addWidget(addRandomIndividualsHowManyValue);
    vb->addLayout(hb);
    optimalizationBox->setLayout(vb);
    optionLayout->addWidget(optimalizationBox, 8, 0, 1, 3);
    /*Widzet pomagajcy w rozmieszczeniu */
    emptyWidget = new QWidget;
    emptyWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    optionLayout->addWidget(emptyWidget, 9,3);
}

Settings::squareType Options::getSquareType()
{
    if(squareTypeButtons[0]->isChecked())
        return Settings::diagonalsCount;
    if(squareTypeButtons[1]->isChecked())
        return Settings::diagonalsNotCount;
    throw "nothing is checked in square buttons";
}

Settings::selectionType Options::getSelectionType()
{
    if(selectionTypeButtons[0]->isChecked())
        return Settings::ranking;
    if(selectionTypeButtons[1]->isChecked())
        return Settings::rulete;
    if(selectionTypeButtons[2]->isChecked())
        return Settings::best;
    throw "nothing is checked in selection buttons";
}

Settings::algorithmType Options::getAlgorithmType()
{
    if(algorithmStrategyButtons[0]->isChecked())
        return Settings::alphaPlusMi;
    if(algorithmStrategyButtons[1]->isChecked())
        return Settings::alphaMi;
    throw "nothing is checked in algorithm buttons";
}

Settings::mutationType Options::getMutationType()
{
    if(mutationTypeButtons[0]->isChecked())
        return Settings::swapFields;
    if(mutationTypeButtons[1]->isChecked())
        return Settings::swapRowsColumns;
    throw "nothing is checked in mutation buttons";
}

Settings::reproductionType Options::getReproductionType()
{
    if(reproductionTypeButtons[0]->isChecked())
        return Settings::saveDiagonals;
    if(reproductionTypeButtons[1]->isChecked())
        return Settings::saveColumns;
    if(reproductionTypeButtons[2]->isChecked())
        return Settings::saveRows;
    throw "nothing is checked in reproductionType";
}

int Options::getLambda()
{
    unsigned int result = (unsigned int)lambdaSizeBox->value();
    if(result < MIN_LAMBDA_VALUE || result > MAX_LAMBDA_VALUE)
        throw "alpha size out of range";
    return result;
}

int Options::getMi()
{
    unsigned int result = (unsigned int)miSizeBox->value();
    if(result < MIN_MI_VALUE || result > MAX_MI_VALUE)
        throw "mi size out of range";
    return result;
}

int Options::getSquareSize()
{
    unsigned int result = (unsigned int)squareSizeBox->value();
    if(result < MIN_SQUARE_SIZE || result > MAX_SQUARE_SIZE)
        throw "square size out of range";
    return result;
}

int Options::getCutPopulationValue()
{
    if(cutPopulationCheckBox->isChecked() == true)
        return cutPopulationValue->value();
    return 0;
}

int Options::getAddNewIndividualsInterval()
{
    if(addRandomIndividualsCheckBox->isChecked() == true)
        return addRandomIndividualsHowFrequentValue->value();
    return 0;
}

int Options::getAddNewIndividualsValue()
{
    if(addRandomIndividualsCheckBox->isChecked() == true)
        return addRandomIndividualsHowManyValue->value();
    return 0;
}

double Options::getMinSigma()
{
    qDebug() << double((double)minPropabilitySlider->value())/100.0;
    return ((double)minPropabilitySlider->value())/100.0;
}

double Options::getMaxSigma()
{
    qDebug() << double((double)maxPropabilitySlider->value())/100.0;
    return ((double)maxPropabilitySlider->value())/100.0;
}

void Options::setMinPropabilityValue(int value)
{
    minPropabilityValue->setText(QString::number((float)value/100.0));
    if(maxPropabilitySlider->value() < value)
    {
        maxPropabilitySlider->setValue(value);
    }
}

void Options::setMaxPropabilityValue(int value)
{
    maxPropabilityValue->setText(QString::number((float)value/100.0));
    if(minPropabilitySlider->value() > value)
    {
        minPropabilitySlider->setValue(value);
    }
}

void Options::setMinimumCut(int value)
{
    cutPopulationValue->setMinimum(miSizeBox->value() + lambdaSizeBox->value());
}
