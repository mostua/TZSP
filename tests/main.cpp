#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <set>
#include "../../model/population.h"
#include "../../model/square.h"
#include "../../model/reproduction.h"
#include "../../model/mutation.h"
#include "../../model/fitness.h"

using namespace std;


void perform(int reproducesNumber, Population &population, Square best)
{
    int i = 1;
    do
    {
        population.generateNextPopulation(reproducesNumber);
        best = population.getBest();
        cout << "Iteration " << i++ << " best far now " << population.countFitness(&best) << endl;
        if(i % 100 == 0)
            population.addNewIndividuals(reproducesNumber);
    } while (population.countFitness(&best) != 0);
    cout << "Result: fitness = " << population.countFitness(&best) << endl;
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
    try{
        Population population(squareSize,reproductionAvaiable, mutation::swapToPoints, fitness::diagonalsAreImportant, reproduction::reproductionFunction);
        Square best(squareSize);
        perform(reproductionAvaiable, population, best);
     }catch(const char * ex)
    {
        cout << ex;
    }

    /*
    srand(time(0));
    Square a(3);
    a.randomFill();
    cout << a;
    cout << *mutation::swapToRows(&a);
    Square b(4);
    b.randomFill();
    cout << b;
    cout << *mutation::swapToColumns(&b);
    cout <<	*mutation::swapToPoints(&a);*/
    system("pause");

}
