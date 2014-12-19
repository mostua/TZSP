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
};

const int MAX_SQUARE_SIZE = 8;
const int MAX_MI_VALUE = 10000;
const int MAX_ALPHA_VALUE = 10000;

#endif // MODEL_H
