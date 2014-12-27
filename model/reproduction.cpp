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
    //zwroc pare dzieci
    return make_pair(childA, childB);
}

