#include "settings.h"

Settings::Settings(int _squareSize, int _alpha, int _mi, selectionType _sel, squareType _sqr, reproductionType _rep, mutationType _mut, simulationType _sim, int param)
                   : squareSize(_squareSize), alpha(_alpha), mi(_mi), selectionTypeValue(_sel), squareTypeValue(_sqr), reproductionTypeValue(_rep), mutationTypeValue(_mut), simulationTypeValue(_sim), simulationParameter(param)
{
}

int Settings::getSquareSize() const
{
    return squareSize;
}
int Settings::getAlpha() const
{
    return alpha;
}

int Settings::getMi() const
{
    return mi;
}

Settings::selectionType Settings::getSelectionTypeValue() const
{
    return selectionTypeValue;
}

Settings::squareType Settings::getSquareTypeValue() const
{
    return squareTypeValue;
}

Settings::reproductionType Settings::getReproductionTypeValue() const
{
    return reproductionTypeValue;
}

Settings::mutationType Settings::getMutationTypeValue() const
{
    return mutationTypeValue;
}

Settings::simulationType Settings::getSimulationTypeValue() const
{
    return simulationTypeValue;
}

int Settings::getSimulationParameter() const
{
    return simulationParameter;
}

