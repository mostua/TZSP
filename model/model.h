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

const int MIN_SQUARE_SIZE = 3;
const int MAX_SQUARE_SIZE = 8;
const int MIN_MI_VALUE = 10;
const int MAX_MI_VALUE = 10000;
const int MIN_ALPHA_VALUE = 10;
const int MAX_ALPHA_VALUE = 10000;
const int MIN_STEPS_VALUE = 1;
const int MAX_STEPS_VALUE = 50;
const int MIN_STEPS_PER_SECOND = 1;
const int MAX_STEPS_PER_SECOND = 50;

#endif // MODEL_H
