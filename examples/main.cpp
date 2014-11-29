#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <set>
#include "population.h"
#include "square.h"
#include "reproduction.h"
#include "mutation.h"

using namespace std;

//fitness function measure how square is far from being magic square
template<unsigned int size>
int fitnessFunction(const Square<size>&);

//function returns fitness of square measered as a sum of distances from befor calculated sum in row/column/diagonal to sum of every row, column and diagonal 
//see in code
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
		diagonalSum += square.get(i,i);
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




template<unsigned int size>
void perform(int reproducesNumber, Population<size> &population, Square<size> &best)
{
    int i = 1;
	do
	{
        population.generateNextPopulation(reproducesNumber, mutation::swapToPoints, fitnessFunction, reproduction::reproductionFunction);
		best = population.getBest(fitnessFunction);
        cout << "Iteration " << i++ << " best far now " << fitnessFunction(best) << endl;
	} while (fitnessFunction(best) != 0);
	cout << "Result: fitness = " << fitnessFunction(best) << endl;
	cout << best << endl;
}




int main()
{
	srand((unsigned int)(time(NULL)));
    unsigned int  squareSize, populationSize, reproductionAvaiable;
    cout << "Please give square size: " << endl;
	cin >> squareSize;
    cout << "Please give begin population size: " << endl;
    cin >> populationSize;
    cout << "Please give number of individuals abvaiable to reproduction" << endl;
    cin >> reproductionAvaiable;
	if (squareSize == 3)
	{
        Population<3> population(reproductionAvaiable);
		Square<3> best;
        perform(reproductionAvaiable, population, best);
	}
	if (squareSize == 4)
	{
        Population<4> population(reproductionAvaiable);
		Square<4> best;
        perform(reproductionAvaiable, population, best);
	}
	if (squareSize == 5)
	{
        Population<5> population(reproductionAvaiable);
		Square<5> best;
        perform(reproductionAvaiable, population, best);
	}

	
	

	system("pause");
}
