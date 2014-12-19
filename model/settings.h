#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{

public:
    enum algorithmType {alphaPlusMi,alphaMi}; //rodzaj algorytmu
    enum strategyType {ranking,random,best}; //rodzaj strategii
    enum squareType{diagonalsCount,diagonalsNotCount}; //rodzaj magicznego kwadratu
    enum reproductionType{saveDiagonals, saveColumns, saveRows}; //rodzaj rozmnazania
    enum mutationType{swapFields,swapRowsColumns}; //rodzaj mutacji
    enum simulationType{stepByStep,fewStepsPerSecond}; //rodzaj
    Settings(int _squareSize, int _alpha, int _mi, strategyType _str, squareType _sqr, reproductionType _rep, mutationType _mut, simulationType _sim, int param);
private:
    int alpha;
    int mi;
    int squareSize;
    strategyType strategyTypeValue;
    squareType squareTypeValue;
    reproductionType reproductionTypeValue;
    mutationType mutationTypeValue;
    simulationType simulationTypeValue;
    int simulationParametr;
};

#endif // SETTINGS_H
