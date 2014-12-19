#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
private:
    int alpha;
    int mi;
    int squareSize;
public:
    enum strategyType {ranking,random,best};
    enum fitnessType{diagonalsCount,diagonalsNotCount};
    enum reproductionType{saveDiagonals, saveColumns, saveRows};
    enum mutationType{swapFields,swapRowsColumns};
    Settings();
};

#endif // SETTINGS_H
