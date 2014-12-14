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

#endif // MODEL_H
