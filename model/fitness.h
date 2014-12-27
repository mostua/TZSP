#ifndef FITNESS_H
#define FITNESS_H

#include "square.h"


//przestrzen nazw zawiera wszystkie funkcje dopasowania
namespace fitness
{
    typedef int (*fitnessFunction)(const Square *);
    //przekątne maja znaczenie
    int onlyRowsAndColumns(const Square* square);
    //przekątne maja znaczenie
    int diagonalsAreImportant(const Square* square);
}

#endif
