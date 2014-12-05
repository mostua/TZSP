//function returns fitness of square measered as a sum of distances from befor calculated sum in row/column/diagonal to sum of every row, column and diagonal 
//see in code
#include "square.h"

namespace fitness
{
	template<unsigned int size>
	int fitnessFunction(const Square<size>& square)
	{
		int result = 0;
		int currentSumInRow, currentSumInCoumn, diagonalSum;
		int fitnessSum = size*(size * size + 1) / 2;
		for (int i = 0; i < size; ++i)
		{
			currentSumInRow = currentSumInCoumn = 0;
			//for each row and column sum values of littles squares
			for (int j = 0; j < size; ++j)
			{
				currentSumInRow += square.get(i, j);
				currentSumInCoumn += square.get(j, i);
			}
			//sum results of absolut diffrance of sum calculated befor and sum in a row/column
			result += abs(fitnessSum - currentSumInRow) + abs(fitnessSum - currentSumInCoumn);
		}
		diagonalSum = 0;
		for (int i = 0; i < size; ++i)
		{
			diagonalSum += square.get(i, i);
		}
		result += abs(fitnessSum - diagonalSum);

		diagonalSum = 0;
		for (int i = 0; i < size; ++i)
		{
			diagonalSum += square.get(i, size - i - 1);
		}
		result += abs(fitnessSum - diagonalSum);
		return result;
	}
}
