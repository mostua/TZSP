#ifndef SETTINGS_H
#define SETTINGS_H

#include "reproduction.h"
#include "mutation.h"
#include "fitness.h"
#include "square.h"
#include "selection.h"



class Settings
{

public:
    enum algorithmType {alphaPlusMi,alphaMi}; //rodzaj algorytmu
    enum selectionType {ranking,rulete,best}; //rodzaj strategii
    enum squareType{diagonalsCount,diagonalsNotCount}; //rodzaj magicznego kwadratu
    enum reproductionType{saveDiagonals, saveColumns, saveRows}; //rodzaj rozmnazania
    enum mutationType{swapFields,swapRowsColumns}; //rodzaj mutacji
    enum simulationType{stepsByStep,fewStepsPerSecond}; //rodzaj symulacji, kilka krokow na jedno klikcnieie, kilka krokow na sekunde
    Settings(int _squareSize, int _mi, int _lambda, selectionType _sel, squareType _sqr, reproductionType _rep, mutationType _mut, simulationType _sim, int param, algorithmType _alg);
    Settings();
    int getSquareSize() const;
    int getMi() const;
    int getLambda() const;
    selectionType getSelectionTypeValue() const;
    selection::selectionFunction getSelectionTypeFunction() const;
    squareType getSquareTypeValue() const;
    fitness::fitnessFunction getSquareTypeFunction() const;
    reproductionType getReproductionTypeValue() const;
    reproduction::reproductionFunction getReproductionTypeFunction() const;
    mutationType getMutationTypeValue() const;
    mutation::mutationFunction getMutationTypeFunction() const;
    simulationType getSimulationTypeValue() const;
    int getSimulationParameter() const;
    algorithmType getAlgorithmType() const;
private:
    int squareSize;
    int lambda;
    int mi;
    selectionType selectionTypeValue;
    squareType squareTypeValue;
    reproductionType reproductionTypeValue;
    mutationType mutationTypeValue;
    simulationType simulationTypeValue;
    int simulationParameter;
    algorithmType algorithmTypeValue;
};

#endif // SETTINGS_H
