#include "reproduction.h"

//przestrzen nazw zawierajaca funkcje reprodukcji

pair<Square*, Square*> reproduction::childHasSameDiagonals(const Square* parentA, const Square* parentB)
{
    //stworz dzieci jako kopie rodzicow
    Square* childA, * childB;
    if(parentA->getSize() != parentB->getSize())
        throw "diffrent side sizes";
    unsigned int size = parentA->getSize();
    childA = new Square(*parentA);
    childB = new Square(*parentB);
    //zamien odpowiednie wartosci na przekatnej
    int x, y;
    for (unsigned int i = 0; i < size; ++i)
    {
        x = childA->get(i, i);
        y = parentB->get(i, i);
        childA->swapValues(x, y);
    }
    //analogicznie zrob dla drugiej przekatnej, z pominieciem srodkowego elemtnu
    for (unsigned int i = 0; i < size; ++i)
    {
        if (size % 2 == 1 && size / 2 == i)
            continue;
        x = childA->get(size - i - 1, i);
        y = parentB->get(size - i - 1, i);
        childA->swapValues(x, y);
    }
    //zrob to samo dla 2 dziecka
    for (unsigned int i = 0; i < size; ++i)
    {
        x = childB->get(i, i);
        y = parentA->get(i, i);
        childB->swapValues(x, y);
    }
    for (unsigned int i = 0; i < size; ++i)
    {
        if (size % 2 == 1 && size / 2 == i)
            continue;
        x = childB->get(size - i - 1, i);
        y = parentA->get(size - i - 1, i);
        childB->swapValues(x, y);
    }
    childA->mutationPropability = (parentA->mutationPropability + parentB->mutationPropability)/2.0;
    childB->mutationPropability = (parentA->mutationPropability + parentB->mutationPropability)/2.0;
    //zwroc pare dzieci
    return make_pair(childA, childB);
}



pair<Square *, Square *> reproduction::childHasSameColumns(const Square *parentA, const Square *parentB)
{
    //stworz dzieci jako kopie rodzicow
    Square* childA, * childB;
    if(parentA->getSize() != parentB->getSize())
        throw "diffrent side sizes";
    unsigned int size = parentA->getSize();
    childA = new Square(*parentA);
    childB = new Square(*parentB);
    int * tabColumns = new int[size];
    for(int i = 0; i < size; ++i)
    {
        tabColumns[i] = i;
    }
    random_shuffle(tabColumns, tabColumns + size); //wypelniona tablice liczbami kolumn poprzestawiaj
    //zamien odpowiednie wartosci na kolumnach
    int x, y;
    for (unsigned int i = 0; i < size; ++i)
    {
        for(unsigned int j = 0; j < size/2; ++j) //dla polowy pierwszych kolumn zrob operacje
        {
            for(unsigned int k = 0; k < size; ++k)
            {
                x = childA->get(k, tabColumns[j]);
                y = parentB->get(k, tabColumns[j]);
                childA->swapValues(x, y);
            }
        }
    }

    //zrob to samo dla 2 dziecka
    for (unsigned int i = 0; i < size; ++i)
    {
        for(unsigned int j = 0; j < size/2; ++j) //dla polowy pierwszych kolumn zrob operacje
        {
            for(unsigned int k = 0; k < size; ++k)
            {
                x = childB->get(k, tabColumns[j]);
                y = parentA->get(k, tabColumns[j]);
                childA->swapValues(x, y);
            }
        }
    }
    childA->mutationPropability = (parentA->mutationPropability + parentB->mutationPropability)/2.0;
    childB->mutationPropability = (parentA->mutationPropability + parentB->mutationPropability)/2.0;

    //zwroc pare dzieci
    return make_pair(childA, childB);
}


pair<Square *, Square *> reproduction::childHasSameRows(const Square *parentA, const Square *parentB)
{
    //stworz dzieci jako kopie rodzicow
    Square* childA, * childB;
    if(parentA->getSize() != parentB->getSize())
        throw "diffrent side sizes";
    unsigned int size = parentA->getSize();
    childA = new Square(*parentA);
    childB = new Square(*parentB);
    int * tabRows = new int[size];
    for(int i = 0; i < size; ++i)
    {
        tabRows[i] = i;
    }
    random_shuffle(tabRows, tabRows + size); //wypelniona tablice liczbami wierszy poprzestawiaj
    //zamien odpowiednie wartosci na wierszach
    int x, y;
    for (unsigned int i = 0; i < size; ++i)
    {
        for(unsigned int j = 0; j < size/2; ++j) //dla polowy pierwszych wieszy zrob operacje
        {
            for(unsigned int k = 0; k < size; ++k)
            {
                x = childA->get(tabRows[j], k);
                y = parentB->get(tabRows[j], k);
                childA->swapValues(x, y);
            }
        }
    }

    //zrob to samo dla 2 dziecka
    for (unsigned int i = 0; i < size; ++i)
    {
        for(unsigned int j = 0; j < size/2; ++j) //dla polowy pierwszych wierszy zrob operacje
        {
            for(unsigned int k = 0; k < size; ++k)
            {
                x = childB->get(tabRows[j], k);
                y = parentA->get(tabRows[j], k);
                childA->swapValues(x, y);
            }
        }
    }
    //zwroc pare dzieci
    childA->mutationPropability = (parentA->mutationPropability + parentB->mutationPropability)/2.0;
    childB->mutationPropability = (parentA->mutationPropability + parentB->mutationPropability)/2.0;

    return make_pair(childA, childB);
}
