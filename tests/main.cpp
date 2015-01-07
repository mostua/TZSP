#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <set>
#include "../model/population.h"
#include "../model/square.h"
#include "../model/reproduction.h"
#include "../model/mutation.h"
#include "../model/fitness.h"
#include "../model/selection.h"
using namespace std;


Population *population;


int main()
{

    srand((unsigned int)(time(NULL)));
    /*unsigned int  squareSize, populationSize, reproductionAvaiable;
    cout << "Please give square size: " << endl;
    cin >> squareSize;
    cout << "Please give begin population size: " << endl;
    cin >> populationSize;
    cout << "Please give number of individuals abvaiable to reproduction" << endl;
    cin >> reproductionAvaiable;
    Square best(3,  fitness::diagonalsAreImportant);
    try
    {
            population = new Population(squareSize, populationSize, reproductionAvaiable, mutation::swapTwoPoints, fitness::diagonalsAreImportant, selection::rankingSelection, reproduction::childHasSameDiagonals);

            int i = 1;
            do
            {
                population->generateNextPopulation();
                best = population->getBest();
                cout <<  "Iteration " << i++ << " best far now " << population->countFitness(&best) << " Population size: "  << population->getPopulationSize() << endl;
                if(i % 100 == 0)
                   population->addNewIndividuals(reproductionAvaiable);
            } while (population->countFitness(&best) != 0);
    }catch(const char * ex)
    {
        cout << ex;
    }
    cout <<  "Finished, best " << population->countFitness(&best) << " Population size: "  << population->getPopulationSize() << endl;

    system("pause");*/

    Square a(3, fitness::diagonalsAreImportant);
    Square b(3, fitness::diagonalsAreImportant);
    a.randomFill();
    b.randomFill();
    cout << a << endl;
    cout << b << endl;
    pair<Square*, Square*> result = reproduction::childHasSameColumns(&a, &b);

    cout << *result.first << endl;
    cout << *result.second << endl;

}
