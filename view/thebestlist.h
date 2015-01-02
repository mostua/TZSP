#ifndef THEBESTLIST_H
#define THEBESTLIST_H

#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include <QGridLayout>
#include <QHeaderView>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include "../model/square.h"
#include "../model/model.h"

class TheBestList : public QWidget
{
    Q_OBJECT
public:
    explicit TheBestList(QWidget *parent = 0);
signals:

public slots:
    void squareSizeChanged(int);
    void updateBest(vectorSquares best);
private slots:
    void showSquare(int row, int column);
private:
    /* tabelka z lista magicznych kwadratow */
    QTableWidget *individualList;
    /* tabelka z zawartoscia magicznego kwadratu */
    QTableWidget *squareResultTable;
    vectorSquares saved;
    void createItems();
    void setWidgetLayout();
    void createConnections();
};


#endif // THEBESTLIST_H
