#ifndef REPRODUCTION_H
#define REPRODUCTION_H
#include "square.h"



//przestrzen nazw zawierajaca funkcje reprodukcji
namespace reproduction
{
    typedef pair<Square*, Square*> (*reproductionFunction)(const Square* parentA, const Square* parentB);
    //funkcja zwraca pare dzieci kazde z nich ma przekatne rodzica (jedno jednego, drugie drugiego)
    pair<Square*, Square*> childHasSameDiagonals(const Square* parentA, const Square* parentB);
}

#endif
