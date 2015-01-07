#ifndef REPRODUCTION_H
#define REPRODUCTION_H
#include "square.h"



//przestrzen nazw zawierajaca funkcje reprodukcji
namespace reproduction
{
    typedef pair<Square*, Square*> (*reproductionFunction)(const Square* parentA, const Square* parentB);
    //funkcja zwraca pare dzieci kazde z nich ma przekatne rodzica (jedno jednego, drugie drugiego)
    pair<Square*, Square*> childHasSameDiagonals(const Square* parentA, const Square* parentB);
    //funkcja zwraca pare dzieci kazde z nich ma polowe kolumn rodzica (jedno jednego, drugie drugiego) (kolumny sa losowo dobierane)
    pair<Square*, Square*> childHasSameColumns(const Square *parentA, const Square* parentB);
    //funkcja zwraca pare dzieci kazde z nich ma polowe wierszy rodzica (jedno jednego, drugie drugiego0 (wiersze sa losowo dobierane)
    pair<Square*, Square*> childHasSameRows(const Square *parentA, const Square* parentB);
}

#endif
