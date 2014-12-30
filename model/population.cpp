#include "population.h"

Population::Population(unsigned int squareSize, unsigned int miValue, unsigned int lambdaValue, Square*(*mutationFunction)(const Square*), int(*fitnessFunction)(const Square*), vector< Square *> (*selectionFunction)(set<Square *, Square::cmp>, unsigned int, unsigned int), pair< Square*, Square* >(*reproductionFunction)(const Square *, const Square *)) : squareSize(squareSize), miValue(miValue), lambdaValue(lambdaValue), mutationFunction(mutationFunction), fitnessFunction(fitnessFunction), selectionFunction(selectionFunction), reproductionFunction(reproductionFunction)
{
    if (squareSize <= 0)
    {
        throw "square size should be greather than 0";
    }
    if (miValue <= 0)
    {
        throw "population should has individuals";
    }
    setSize = 0;
    addNewIndividuals(miValue);
    //wartosc prawd. mutacji domyslnie 1/2
    setMutationPropability(1, 2);
}


void Population::generateNextPopulation()
{
    //sortujemy wg. wsp. dopasowania
    vector<Square *> reproducers = selectionFunction(population, setSize, lambdaValue);
    random_shuffle(reproducers.begin(), reproducers.end());
    vector<Square *> children;
    for (unsigned int i = 0; 2 * i + 1 < min((size_t)lambdaValue, reproducers.size()) - min((size_t)lambdaValue, reproducers.size()) % 2; i++)
    {
        pair<Square*,Square*> result = reproductionFunction(reproducers.at(2 * i), reproducers.at(2 * i + 1));
        //z danym prawd. mutujemy dzieci
        if (rand() % qMutation < pMutation)
            result.first = mutationFunction(result.first);
        if (rand() % qMutation < pMutation)
            result.second = mutationFunction(result.second);
        children.push_back(result.first);
        children.push_back(result.second);
    }
    //TODO w zależoności od rodzaju algorytmu, albo dodajemu na koncu ale tworzymy nowa populacje
    for(Square * e : children){
        population.insert(e);
        setSize++;
    }
}



void Population::setMutationPropability(int p, int q)
{
    pMutation = p;
    qMutation = q;
}


unsigned int Population::getPopulationSize()
{
    return setSize;
}


Square Population::getBest()
{ 
    return **population.begin();
}

double Population::populationAverage()
{
    long long sum = 0;
    for (auto it = population.begin(); it != population.end(); ++it)
    {
        sum += fitnessFunction(*it);
    }
    return ((double)sum) / setSize;

}

void Population::addNewIndividuals(int howMany)
{
    Square * temp;
    if (howMany <= 0)
        throw "wrong number of new individuals";
    for (int i = 0; i < howMany; ++i)
    {
        temp = new Square(squareSize, fitnessFunction);
        temp->randomFill();
        population.insert(temp);
        setSize++;
    }
}

int Population::countFitness(const Square *invid)
{
    return fitnessFunction(invid);
}
