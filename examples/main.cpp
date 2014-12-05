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
        population.generateNextPopulation(reproducesNumber, mutation::swapToPoints, fitness::fitnessFunction, reproduction::reproductionFunction);
		best = population.getBest(fitness::fitnessFunction);
        cout << "Iteration " << i++ << " best far now " << fitness::fitnessFunction(best) << endl;
	} while (fitness::fitnessFunction(best) != 0);
	cout << "Result: fitness = " << fitness::fitnessFunction(best) << endl;
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
