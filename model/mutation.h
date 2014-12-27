#ifndef MUTATION_H
#define MUTATION_H
#include "square.h"
#include <vector>


//przestrzen nazw zawierajaca wszystkie funkcje mutacji
namespace mutation
{
    typedef Square* (*mutationFunction)(const Square *);
    //mutacja zmieniajace dwa punkty miedzy sob¹
    Square* swapTwoPoints(const Square * square);
    //mutacja zmieniajace dwie kolumny miedzy soba
    Square* swapTwoColumns(const Square * square);
    //mutacja zmieniajaca dwa wierszy miedzy soba
    Square* swapTwoRows(const Square * square);
}

#endif
