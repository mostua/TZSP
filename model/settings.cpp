#include "settings.h"

Settings::Settings(int _squareSize, int _alpha, int _mi, strategyType _str, squareType _sqr, reproductionType _rep, mutationType _mut, simulationType _sim, int param)
                   : squareSize(_squareSize), alpha(_alpha), mi(_mi), strategyTypeValue(_str), squareTypeValue(_sqr), reproductionTypeValue(_rep), mutationTypeValue(_mut), simulationTypeValue(_sim), simulationParametr(param)
{
}
