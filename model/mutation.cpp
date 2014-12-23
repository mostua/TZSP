#include "mutation.h"

Square* mutation::swapToPoints(const Square * square)
{
   Square * result = new Square(*square);
    int size = square->getSize();
    int ax, ay, av, bx, by, bv;
    ax = rand() % size;
    ay = rand() % size;
    av = result->get(ay, ax);
    bx = rand() % size;
    by = rand() % size;
    bv = result->get(by, bx);
    result->set(by, bx, av);
    result->set(ay, ax, bv);
    return result;
}

Square* mutation::swapToColumns(const Square * square)
{
    Square * result = new Square(*square);
    int columna, columnb;
    //losujemy sposrod 3 kolumn
    vector<int> tab;
    for (unsigned int i = 0; i <  result->getSize(); i++) { tab.push_back(i); }
    random_shuffle(tab.begin(), tab.end());
    columna = tab[0], columnb = tab[1];
    for (unsigned int i = 0; i < result->getSize(); ++i)
    {
        result->swapPoints(i, columna, i, columnb);
    }
    return result;
}

Square* mutation::swapToRows(const Square * square)
{
    Square * result = new Square(*square);
    int rowa, rowb;
    //losujemy sposrod 3 wierszy
    vector<int> tab;
    for (unsigned int i = 0; i < result->getSize(); i++) { tab.push_back(i); }
    random_shuffle(tab.begin(), tab.end());
    rowa = tab[0], rowb = tab[1];
    for (unsigned int i = 0; i < result->getSize(); ++i)
    {
        result->swapPoints(rowa, i, rowb, i);
    }
    return result;
}
