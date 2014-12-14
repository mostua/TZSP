#include "square.h"


//przestrzen nazw zawiera wszystkie funkcje dopasowania
namespace fitness
{
    //przek¹tne maja znaczenie
    template<unsigned int size>
    int onlyRowsAndColumns(const Square<size>& square)
    {
        int result = 0;
        int currentSumInRow, currentSumInCoumn;
        int fitnessSum = size*(size * size + 1) / 2;
        for (unsigned int i = 0; i < size; ++i)
        {
            currentSumInRow = currentSumInCoumn = 0;
            //dla kazdej kolumny policz sume, oraz dla kazdego wiersza
            for (unsigned int j = 0; j < size; ++j)
            {
                currentSumInRow += square.get(i, j);
                currentSumInCoumn += square.get(j, i);
            }
            //do wyniku dodaj roznice miedzy porzadana suma a otrzymana (dla kazdej kolumny i wiersza)
            result += abs(fitnessSum - currentSumInRow) + abs(fitnessSum - currentSumInCoumn);
        }
        return result;
    }
    //przek¹tne maja znaczenie
    template<unsigned int size>
    int diagonalsAreImportant(const Square<size>& square)
    {
        int result = 0;
        int diagonalSum;
        int fitnessSum = size*(size * size + 1) / 2;
        result += onlyRowsAndColumns(square);
        diagonalSum = 0;
        for (unsigned int i = 0; i < size; ++i)
        {
            diagonalSum += square.get(i, i);
        }
        result += abs(fitnessSum - diagonalSum);
        diagonalSum = 0;
        for (unsigned int i = 0; i < size; ++i)
        {
            diagonalSum += square.get(i, size - i - 1);
        }
        result += abs(fitnessSum - diagonalSum);
        return result;
    }
}
