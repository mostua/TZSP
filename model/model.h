#ifndef MODEL_H
#define MODEL_H

#include "population.h"
#include "reproduction.h"
#include "fitness.h"
#include "reproduction.h"
#include "mutation.h"

template<unsigned int size>
struct Model
{
    Population<size> * population;
    enum strategyType {ranking,random,best};
    enum fitnessType{diagonalsCount,diagonalsNotCount};
    enum reproductionType{saveDiagonals, saveColumns, saveRows};
    enum mutationType{swapFields,swapRowsColumns};
};

const int MAX_SQUARE_SIZE = 8;

#endif // MODEL_H
