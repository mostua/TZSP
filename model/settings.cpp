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

fitness::fitnessFunction Settings::getSquareTypeFunction() const
{
    switch (getSelectionTypeValue())
    {
    case diagonalsCount:
        return fitness::diagonalsAreImportant;
    case diagonalsNotCount:
    default:
        return fitness::onlyRowsAndColumns;
    }
}

Settings::reproductionType Settings::getReproductionTypeValue() const
{
    return reproductionTypeValue;
}

reproduction::reproductionFunction Settings::getReproductionTypeFunction() const
{
    switch (getReproductionTypeValue())
    {
    case saveDiagonals:
        return reproduction::childHasSameDiagonals;
    case saveColumns:
    case saveRows:
    default:
        throw "not implemented";
    }
}

Settings::mutationType Settings::getMutationTypeValue() const
{
    return mutationTypeValue;
}

mutation::mutationFunction Settings::getMutationTypeFunction() const
{
    switch(getMutationTypeValue())
    {
    case swapFields:
        return mutation::swapTwoRows;
    case swapRowsColumns:
    default:
        return mutation::swapTwoColumns;
    }
}

Settings::simulationType Settings::getSimulationTypeValue() const
{
    return simulationTypeValue;
}

int Settings::getSimulationParameter() const
{
    return simulationParameter;
}

