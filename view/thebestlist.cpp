#include "thebestlist.h"

TheBestList::TheBestList(QWidget *parent)
{
    createItems();
    setWidgetLayout();
    createConnections();
}

void TheBestList::squareSizeChanged(int value)
{
    while(squareResultTable->columnCount() < value)
        squareResultTable->insertColumn(squareResultTable->columnCount());
    while(squareResultTable->rowCount() < value)
        squareResultTable->insertRow( squareResultTable->rowCount());
    while(squareResultTable->columnCount() > value)
        squareResultTable->removeColumn(squareResultTable->columnCount() - 1);
    while(squareResultTable->rowCount() > value)
        squareResultTable->removeRow(squareResultTable->rowCount() - 1);
}

void TheBestList::updateBest(vectorSquares best)
{

    saved = best;
    for(unsigned int i = 0; i < min((unsigned)saved.size(), (unsigned)HOW_MANY_BEST_SHOW); i++)
    {
        individualList->setItem(i, 0, new QTableWidgetItem(QString("%1").arg(saved[i].first)));
        individualList->setItem(i, 1, new QTableWidgetItem(QString("%1").arg(saved[i].second.first)));
    }
}

void TheBestList::showSquare(int row, int column)
{
    qDebug() << "showSquare";
    int i = 0;
    int squareSize = squareResultTable->rowCount();
    if(squareResultTable->rowCount() != squareResultTable->columnCount())
    {
        throw "rectangle is not a square";
    }
    if(row >= 0 && row < saved.size())
    {
        for(auto it = saved[row].second.second.begin(); it != saved[row].second.second.end(); ++it, ++i)
        {
            squareResultTable->setItem(i/squareSize, i%squareSize, new QTableWidgetItem(QString("%1").arg(*it)));
        }
    }
}


void TheBestList::setWidgetLayout()
{
    QGridLayout * layout = new QGridLayout();
    layout->addWidget(individualList, 0, 0);
    layout->addWidget(squareResultTable, 0, 1);
    setLayout(layout);
}

void TheBestList::createConnections()
{
    connect(individualList,SIGNAL(cellPressed(int,int)),this, SLOT(showSquare(int,int)));
}


void TheBestList::createItems()
{
    individualList = new QTableWidget(HOW_MANY_BEST_SHOW , 2);
    QStringList columnNames;
    columnNames.append(tr("id"));
    columnNames.append(tr("fitness"));
    individualList->setHorizontalHeaderLabels(columnNames);
    squareResultTable = new QTableWidget(3, 3);
}
