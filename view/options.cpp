#include "options.h"

Options::Options(QWidget *parent) :
    QWidget(parent)
{
    alpha = QChar(0xb1, 0x03);
    mi = QChar(0xbc, 0x03);
    createWidgetItems();
    setWidgetLayout();

}

void Options::createWidgetItems()
{
    /*Suwak do wyboru rozmiaru kwadratu*/
    squareSizeText = new QLabel(tr("Square side size:"));
    squareSizeBox = new QSpinBox();
    squareSizeBox->setRange(3,MAX_SQUARE_SIZE);
    squareSizeBox->setSingleStep(1);
    squareSizeBox->setValue(3);
    /*Suwak do wyboru wielkosci parametru alpha */
    alphaSizeText = new QLabel(QString(alpha) + tr(" parameter value:"));
    alphaSizeBox = new QSpinBox();
    alphaSizeBox->setRange(10,MAX_ALPHA_VALUE);
    alphaSizeBox->setSingleStep(1);
    alphaSizeBox->setValue(10);
    /*Suwak do wyboru wielkosci parametru mi*/
    miSizeText = new QLabel(QString(mi) + tr(" parameter value:"));
    miSizeBox = new QSpinBox();
    miSizeBox->setRange(10,MAX_MI_VALUE);
    miSizeBox->setSingleStep(1);
    miSizeBox->setValue(10);
    /*Grupa przyciskow do wyboru magicznego kwadratu */
    squareTypeBox = new QGroupBox(tr("Square Type Box"));
    squareTypeButtons[0] = new QRadioButton(tr("Diagonals are important"));
    squareTypeButtons[1] = new QRadioButton(tr("Diagonals are not important"));
    squareTypeButtons[0]->setChecked(true);

    /*Grupa przyciskow do wyboru typu strategii */
    algorithmStrategyBox  = new QGroupBox(tr("Algorithm Strategy"));
    algorithmStrategyButtons[0] = new QRadioButton(QString("%1 + %2").arg(alpha, mi));
    algorithmStrategyButtons[1] = new QRadioButton(QString("(%1, %2)").arg(alpha, mi));
    algorithmStrategyButtons[0]->setChecked(true);

    /*Grupa przyciskow do wyboru osobników do rozmnażania */
    selectionTypeBox  = new QGroupBox(tr("Selection Type"));
    selectionTypeButtons[0] = new QRadioButton(tr("Ranking"));
    selectionTypeButtons[1] = new QRadioButton(tr("Random"));
    selectionTypeButtons[2] = new QRadioButton(tr("Propotional"));
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
}


void Options::setWidgetLayout()
{
    /*Głowny layout */
    optionLayout = new QGridLayout();
    setLayout(optionLayout);
    /*Na górze przyciski dotyczace rozmiaru kwadratu */
    optionLayout->addWidget(squareSizeText, 0, 0);
    optionLayout->addWidget(squareSizeBox, 0, 1);
    /*Niżej przyciski dotyczace parametrów alpha i mi */
    optionLayout->addWidget(alphaSizeText, 1, 0);
    optionLayout->addWidget(alphaSizeBox, 1, 1);
    optionLayout->addWidget(miSizeText, 2, 0);
    optionLayout->addWidget(miSizeBox, 2, 1);

    /*Layout w grupie od rodzaju kwadratu */
    QVBoxLayout *vb;
    vb = new QVBoxLayout;
    vb->addWidget(squareTypeButtons[0]);
    vb->addWidget(squareTypeButtons[1]);
    squareTypeBox->setLayout(vb);
    optionLayout->addWidget(squareTypeBox,3,0);
    /*Layout w grupie od rodzaju strategi */
    vb = new QVBoxLayout;
    vb->addWidget(algorithmStrategyButtons[0]);
    vb->addWidget(algorithmStrategyButtons[1]);
    algorithmStrategyBox->setLayout(vb);
    optionLayout->addWidget(algorithmStrategyBox, 4, 0);
    /*Layout w grupie od rodzaju selekcji */
    vb = new QVBoxLayout;
    vb->addWidget(selectionTypeButtons[0]);
    vb->addWidget(selectionTypeButtons[1]);
    vb->addWidget(selectionTypeButtons[2]);
    selectionTypeBox->setLayout(vb);
    optionLayout->addWidget(selectionTypeBox, 5, 0);
    /*Layout w grupie od rodzaju reprodukcji */
    vb = new QVBoxLayout;
    vb->addWidget(reproductionTypeButtons[0]);
    vb->addWidget(reproductionTypeButtons[1]);
    vb->addWidget(reproductionTypeButtons[2]);
    reproductionTypeBox->setLayout(vb);
    optionLayout->addWidget(reproductionTypeBox, 3,1);
    /*Layout w grupie od rodzaju mutacji*/
    vb = new QVBoxLayout;
    vb->addWidget(mutationTypeButtons[0]);
    vb->addWidget(mutationTypeButtons[1]);
    mutationTypeBox->setLayout(vb);
    optionLayout->addWidget(mutationTypeBox, 4,1);
    /*Widzet pomagajcy w rozmieszczeniu */
    QWidget* emptyWidget = new QWidget;
    emptyWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    optionLayout->addWidget(emptyWidget, 6,2);
}

Settings::squareType Options::getSquareType()
{
    if(squareTypeButtons[0]->isChecked())
        return Settings::squareType::diagonalsCount;
    if(squareTypeButtons[1]->isChecked())
        return Settings::squareType::diagonalsNotCount;
    throw "nothing is checked";
}

Settings::strategyType Options::getStrategyType()
{

}

Settings::algorithmType Options::getAlgorithmType()
{

}
