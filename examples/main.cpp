#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <set>
#include "population.h"
#include "square.h"
#include "reproduction.h"
#include "mutation.h"
#include "fitness.h"

using namespace std;

template<unsigned int size>
void perform(int reproducesNumber, Population<size> &population, Square<size> &best)
{
    int i = 1;
	do
	{
		population.generateNextPopulation(reproducesNumber);
		best = population.getBest(fitness::diagonalsAreImportant);
		cout << "Iteration " << i++ << " best far now " << fitness::diagonalsAreImportant(best) << endl;
	} while (fitness::diagonalsAreImportant(best) != 0);
	cout << "Result: fitness = " << fitness::diagonalsAreImportant(best) << endl;
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
		Population<3> population(reproductionAvaiable, mutation::swapToPoints, fitness::diagonalsAreImportant, reproduction::reproductionFunction);
		Square<3> best;
        perform(reproductionAvaiable, population, best);
	}
	if (squareSize == 4)
	{
		Population<4> population(reproductionAvaiable, mutation::swapToPoints, fitness::diagonalsAreImportant, reproduction::reproductionFunction);
		Square<4> best;
        perform(reproductionAvaiable, population, best);
	}
	if (squareSize == 5)
	{
		Population<5> population(reproductionAvaiable, mutation::swapToPoints, fitness::diagonalsAreImportant, reproduction::reproductionFunction);
		Square<5> best;
        perform(reproductionAvaiable, population, best);
	}

	
	

	system("pause");
}
