#include "options.h"

Options::Options(QWidget *parent) :
    QWidget(parent)
{
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
    /*Grupa przyciskow do wyboru magicznego kwadratu */
    squareTypeBox = new QGroupBox(tr("Square Type Box"));
    squareTypeButtons[0] = new QRadioButton(tr("Diagonals are important"));
    squareTypeButtons[1] = new QRadioButton(tr("Diagonals are not important"));
    squareTypeButtons[0]->setChecked(true);

    /*Grupa przyciskow do wyboru typu strategii */
    algorithmStrategyBox  = new QGroupBox(tr("Algorithm Strategy"));
    algorithmStrategyButtons[0] = new QRadioButton(QString("%1 + %2").arg(QChar(0xb1, 0x03),QChar(0xbc, 0x03)));
    algorithmStrategyButtons[1] = new QRadioButton(QString("(%1, %2)").arg(QChar(0xb1, 0x03),QChar(0xbc, 0x03)));
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
    /*Layout w grupie od rodzaju kwadratu */
    QVBoxLayout *vb;
    vb = new QVBoxLayout;
    vb->addWidget(squareTypeButtons[0]);
    vb->addWidget(squareTypeButtons[1]);
    squareTypeBox->setLayout(vb);
    optionLayout->addWidget(squareTypeBox,1,0);
    /*Layout w grupie od rodzaju strategi */
    vb = new QVBoxLayout;
    vb->addWidget(algorithmStrategyButtons[0]);
    vb->addWidget(algorithmStrategyButtons[1]);
    algorithmStrategyBox->setLayout(vb);
    optionLayout->addWidget(algorithmStrategyBox, 2, 0);
    /*Layout w grupie od rodzaju selekcji */
    vb = new QVBoxLayout;
    vb->addWidget(selectionTypeButtons[0]);
    vb->addWidget(selectionTypeButtons[1]);
    vb->addWidget(selectionTypeButtons[2]);
    selectionTypeBox->setLayout(vb);
    optionLayout->addWidget(selectionTypeBox, 3, 0);
    /*Layout w grupie od rodzaju reprodukcji */
    vb = new QVBoxLayout;
    vb->addWidget(reproductionTypeButtons[0]);
    vb->addWidget(reproductionTypeButtons[1]);
    vb->addWidget(reproductionTypeButtons[2]);
    reproductionTypeBox->setLayout(vb);
    optionLayout->addWidget(reproductionTypeBox, 1,1);
    /*Layout w grupie od rodzaju mutacji*/
    vb = new QVBoxLayout;
    vb->addWidget(mutationTypeButtons[0]);
    vb->addWidget(mutationTypeButtons[1]);
    mutationTypeBox->setLayout(vb);
    optionLayout->addWidget(mutationTypeBox, 2,1);
}
