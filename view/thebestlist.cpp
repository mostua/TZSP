#include "thebestlist.h"

TheBestList::TheBestList(QWidget *parent)
{
    createItems();
    setWidgetLayout();
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