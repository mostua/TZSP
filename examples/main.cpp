#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <set>
#include "population.h"
#include "square.h"


using namespace std;

template<unsigned int size>
ostream& operator<<(ostream & os, const Square<size> &square)
{
	os << size << " x " << size << "\n";
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			os << square.get(i, j) << " ";
		os << "\n";
	}
	return os;
}

//fitness function measure how square is far from being magic square
template<unsigned int size>
int fitnessFunction(const Square<size>&);

//function creates two children from two parents, mixing diagonals
template<unsigned int size>
pair<Square<size>, Square<size>> reproductionFunction(const Square<size> &, const Square<size> &);

//function swap 2 points in square
template<unsigned int size>
Square<size> mutationFunction(const Square<size> & square);

//we can sort squares comparing theirs fitness values
template<unsigned int size>
bool cmp(const Square<size>& a, const Square<size>& b)
{
	if (fitnessFunction(a) != fitnessFunction(b))
		return fitnessFunction(a) < fitnessFunction(b);
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			if (a.get(i, j) != b.get(i, j))
				return a.get(i, j) < b.get(i, j);
	}
	return a.id < b.id;
}


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

//reproduction function creates descendants
template<unsigned int size>
pair<Square<size>, Square<size>> reproductionFunction(const Square<size> & parentA, const Square<size> & parentB)
{
	//if (parentA.getSize() != parentB.getSize())
	//	throw "Sheep can't reproduce with human";
	//make one of children with parentA diagonals, and second with parentB diagonals
	//copy child A from parent A and so for child B
	Square<size> childA, childB;
	childA = parentA, childB = parentB;
	//swap (x,x) in childA to value of parentB (x,x) same to (n-x-1, x)
	int x, y;
	for (int i = 0; i < size; ++i)
	{
		x = childA.get(i, i);
		y = parentB.get(i, i);
		childA.swap(x, y);
	}
	for (int i = 0; i < size; ++i)
	{
		if (size % 2 == 1 && size / 2 == i)
			continue;
		x = childA.get(size - i - 1, i);
		y = parentB.get(size - i - 1, i);
		childA.swap(x, y);
	}
	for (int i = 0; i < size; ++i)
	{
		x = childB.get(i, i);
		y = parentA.get(i, i);
		childB.swap(x, y);
	}
	for (int i = 0; i < size; ++i)
	{
		if (size % 2 == 1 && size / 2 == i)
			continue;
		x = childB.get(size - i - 1, i);
		y = parentA.get(size - i - 1, i);
		childB.swap(x, y);
	}
	//return reproduces childs
	pair<Square<size>, Square<size>> result = make_pair(childA, childB);
	return result;
}

//Mutation function swaping two random points in 
template<unsigned int size>
Square<size> mutationFunction(const Square<size> & square)
{
	Square<size> result = square;
	int ax, ay, av, bx, by, bv;
	ax = rand() % size;
	ay = rand() % size;
	av = result.get(ay, ax);
	bx = rand() % size;
	by = rand() % size;
	bv = result.get(by, bx);
	result.set(by, bx, av);
	result.set(ay, ax, bv);
	return result;
}


template<unsigned int size>
void perform(int reproducesNumber, Population<size> &population, Square<size> &best)
{
    int i = 1;
	do
	{
        population.generateNextPopulation(reproducesNumber, cmp, mutationFunction, fitnessFunction, reproductionFunction);
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
