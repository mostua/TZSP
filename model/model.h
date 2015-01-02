#ifndef MODEL_H
#define MODEL_H

#include "population.h"
#include "reproduction.h"
#include "fitness.h"
#include "reproduction.h"
#include "mutation.h"
#include <QVector>

struct Model
{
    Population * population;
};

const unsigned int MIN_SQUARE_SIZE = 3;
const unsigned int MAX_SQUARE_SIZE = 8;
const unsigned int MIN_MI_VALUE = 10;
const unsigned int DEFAULT_MI_VALUE = 1000;
const unsigned int MAX_MI_VALUE = 10000;
const unsigned int MIN_LAMBDA_VALUE = 10;
const unsigned int DEFAULT_LAMBDA_VALUE = 500;
const unsigned int MAX_LAMBDA_VALUE = 10000;
const unsigned int MIN_STEPS_VALUE = 1;
const unsigned int MAX_STEPS_VALUE = 50;
const unsigned int MIN_STEPS_PER_SECOND = 1;
const unsigned int MAX_STEPS_PER_SECOND = 50;
const unsigned int HOW_MANY_BEST_SHOW = 100;
typedef vector< pair<int,int> > vectorPairs;
typedef vector< pair<int, pair<int, vector<int> > > > vectorSquares;

#endif // MODEL_H
