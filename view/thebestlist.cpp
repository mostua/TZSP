#include "thebestlist.h"

TheBestList::TheBestList(QWidget *parent)
{
    createItems();
    setWidgetLayout();
}

void TheBestList::squareSizeChanged(int value)
{
    if(squareResultTable->columnCount() < value)
        squareResultTable->insertColumn(value - squareResultTable->columnCount());
    if(squareResultTable->rowCount() < value)
        squareResultTable->insertRow(value - squareResultTable->rowCount());
    if(squareResultTable->columnCount() > value)
        squareResultTable->removeColumn(squareResultTable->columnCount() - value);
    if(squareResultTable->rowCount() > value)
        squareResultTable->removeRow(squareResultTable->rowCount() - value );

}


void TheBestList::setWidgetLayout()
{
    QGridLayout * layout = new QGridLayout();
    layout->addWidget(individualList, 0, 0);
    layout->addWidget(squareResultTable, 0, 1);
    setLayout(layout);
}

void TheBestList::createItems()
{
    individualList = new QTableView();
    squareResultTable = new QTableWidget(3, 3);
}
