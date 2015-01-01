#ifndef THEBESTLIST_H
#define THEBESTLIST_H

#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include <QGridLayout>
#include <QHeaderView>
#include <QDebug>

class TheBestList : public QWidget
{
    Q_OBJECT
public:
    explicit TheBestList(QWidget *parent = 0);
signals:

public slots:
    void squareSizeChanged(int);

private:
    /* tabelka z lista magicznych kwadratow */
    QTableView *individualList;

    /* tabelka z zawartoscia magicznego kwadratu */
    QTableWidget *squareResultTable;
    void createItems();
    void setWidgetLayout();
};


#endif // THEBESTLIST_H
