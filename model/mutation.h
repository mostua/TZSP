#ifndef MUTATION_H
#define MUTATION_H
#include "square.h"
#include <vector>


//przestrzen nazw zawierajaca wszystkie funkcje mutacji
namespace mutation
{
    //mutacja zmieniajace dwa punkty miedzy sob¹

    Square* swapToPoints(const Square * square);
    //mutacja zmieniajace dwie kolumny miedzy soba

    Square* swapToColumns(const Square * square);
    //mutacja zmieniajaca dwa wierszy miedzy soba

    Square* swapToRows(const Square * square);
}

#endif
