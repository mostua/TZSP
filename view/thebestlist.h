#ifndef THEBESTLIST_H
#define THEBESTLIST_H

#include <QWidget>
#include <QTableView>
#include <QTableWidget>
#include <QGridLayout>
#include <QHeaderView>

class TheBestList : public QWidget
{
    Q_OBJECT
public:
    explicit TheBestList(QWidget *parent = 0);
signals:

private:
    /* tabelka z lista magicznych kwadratow */
    QTableView *individualList;

    /* tabelka z zawartoscia magicznego kwadratu */
    QTableWidget *squareResultTable;
    void createItems();
    void setWidgetLayout();
};


#endif // THEBESTLIST_H
