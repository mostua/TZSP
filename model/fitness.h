#ifndef FITNESS_H
#define FITNESS_H

#include "square.h"


//przestrzen nazw zawiera wszystkie funkcje dopasowania
namespace fitness
{
    //przekštne maja znaczenie
    int onlyRowsAndColumns(const Square* square);
    //przekštne maja znaczenie
    int diagonalsAreImportant(const Square* square);
}

#endif
