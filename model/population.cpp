#include "population.h"

Population::Population(int _squareSize, int beginSize, Square*(*mutationFunction)(const Square*), int(*fitnessFunction)(const Square*), pair< Square*, Square* >(*reproductionFunction)(const Square *, const Square *)) : mutationFunction(mutationFunction), fitnessFunction(fitnessFunction), reproductionFunction(reproductionFunction)
{
    if (_squareSize <= 0)
    {
        throw "square size should be greather than 0";
    }
    squareSize = _squareSize;
    if (beginSize <= 0)
    {
        throw "population should has individuals";
    }
    addNewIndividuals(beginSize);
    //wartosc prawd. mutacji domyslnie 1/2
    setMutationPropability(1, 2);
}


void Population::generateNextPopulation(unsigned int howManyReproduces)
{
    //sortujemy wg. wsp. dopasowania
    sort(population.begin(), population.end(), [this](const Square *a, const Square *b)->bool{ 	return (fitnessFunction(a) != fitnessFunction(b) ? fitnessFunction(a) < fitnessFunction(b) : a < b);  });
    if (population.size() > howManyReproduces)
        population.resize(howManyReproduces);
    population.shrink_to_fit();
    //z tych co sie beda dopasowywac wybieramy losowo rodzicow
    random_shuffle(population.begin(), population.end());
    //we cannot by sure about size of square
    //pair<const Square*, const Square*> result;
    size_t populationSize = population.size();
    for (size_t i = 0; 2 * i + 1 < min((size_t)howManyReproduces, populationSize) - min((size_t)howManyReproduces, populationSize) % 2; i++)
    {
        pair<Square*,Square*> result = reproductionFunction(population.at(2 * i), population.at(2 * i + 1));
        //z danym prawd. mutujemy dzieci
        if (rand() % qMutation < pMutation)
            result.first = mutationFunction(result.first);
        if (rand() % qMutation < pMutation)
            result.second = mutationFunction(result.second);
        population.push_back(result.first);
        population.push_back(result.second);
    }
}



void Population::setMutationPropability(int p, int q)
{
    pMutation = p;
    qMutation = q;
}


unsigned int Population::getPopulationSize()
{
    return population.size();
}


Square Population::getBest()
{
    size_t best = 0;
    for (size_t i = 1; i < population.size(); ++i)
    {
        if (fitnessFunction(population[i]) < fitnessFunction(population[best]))
            best = i;
    }
    return *population[best];
}

double Population::populationAverage()
{
    long long sum = 0;
    for (size_t i = 0; i < population.size(); ++i)
    {
        sum += fitnessFunction(population[i]);
    }
    return ((double)sum) / population.size();

}

void Population::addNewIndividuals(int howMany)
{
    Square * temp;
    if (howMany <= 0)
        throw "wrong number of new individuals";
    for (int i = 0; i < howMany; ++i)
    {
        temp = new Square(squareSize);
        temp->randomFill();
        population.push_back(temp);
    }
}

int Population::countFitness(const Square *invid)
{
    return fitnessFunction(invid);
}
