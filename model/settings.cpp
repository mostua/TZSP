#include "settings.h"


Settings::Settings(int _squareSize, int _mi, int _lambda, selectionType _sel, squareType _sqr, reproductionType _rep, mutationType _mut, simulationType _sim, int param, algorithmType _alg)
                   : squareSize(_squareSize), mi(_mi), lambda(_lambda), selectionTypeValue(_sel), squareTypeValue(_sqr), reproductionTypeValue(_rep), mutationTypeValue(_mut), simulationTypeValue(_sim), simulationParameter(param), algorithmTypeValue(_alg)
{
}

Settings::Settings()
{

}

int Settings::getSquareSize() const
{
    return squareSize;
}
int Settings::getMi() const
{
    return mi;
}

int Settings::getLambda() const
{
    return lambda;
}

Settings::selectionType Settings::getSelectionTypeValue() const
{
    return selectionTypeValue;
}

selection::selectionFunction Settings::getSelectionTypeFunction() const
{
    switch (getSelectionTypeValue())
    {
    case ranking:
        return selection::rankingSelection;
    case rulete:
        return selection::ruleteSelection;
    case best:
    default:
        return selection::bestSelection;
    }
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
        return reproduction::childHasSameColumns;
    case saveRows:
    default:
        return reproduction::childHasSameRows;
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

Settings::algorithmType Settings::getAlgorithmType() const
{
    return algorithmTypeValue;
}

