#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{

public:
    enum algorithmType {alphaPlusMi,alphaMi}; //rodzaj algorytmu
    enum selectionType {ranking,random,best}; //rodzaj strategii
    enum squareType{diagonalsCount,diagonalsNotCount}; //rodzaj magicznego kwadratu
    enum reproductionType{saveDiagonals, saveColumns, saveRows}; //rodzaj rozmnazania
    enum mutationType{swapFields,swapRowsColumns}; //rodzaj mutacji
    enum simulationType{stepsByStep,fewStepsPerSecond}; //rodzaj symulacji, kilka krokow na jedno klikcnieie, kilka krokow na sekunde
    Settings(int _squareSize, int _alpha, int _mi, selectionType _sel, squareType _sqr, reproductionType _rep, mutationType _mut, simulationType _sim, int param);
    int getSquareSize() const;
    int getAlpha() const;
    void setAlpha(int value);
    int getMi() const;
    selectionType getSelectionTypeValue() const;
    squareType getSquareTypeValue() const;
    reproductionType getReproductionTypeValue() const;
    mutationType getMutationTypeValue() const;
    simulationType getSimulationTypeValue() const;
    int getSimulationParameter() const;

private:
    int squareSize;
    int alpha;
    int mi;
    selectionType selectionTypeValue;
    squareType squareTypeValue;
    reproductionType reproductionTypeValue;
    mutationType mutationTypeValue;
    simulationType simulationTypeValue;
    int simulationParameter;
};

#endif // SETTINGS_H
