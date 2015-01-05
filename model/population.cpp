#include "population.h"

Population::Population(unsigned int squareSize, unsigned int miValue, unsigned int lambdaValue, double minSigma, double maxSigma, Square*(*mutationFunction)(const Square*), int(*fitnessFunction)(const Square*), vector< Square *> (*selectionFunction)(set<Square *, Square::cmp>, unsigned int, unsigned int), pair< Square*, Square* >(*reproductionFunction)(const Square *, const Square *), int _algorithmType) : squareSize(squareSize), miValue(miValue), lambdaValue(lambdaValue), mutationFunction(mutationFunction), fitnessFunction(fitnessFunction), selectionFunction(selectionFunction), reproductionFunction(reproductionFunction), algorithmType(_algorithmType)
{
    if (squareSize <= 0)
    {
        throw "square size should be greather than 0";
    }
    if (miValue <= 0)
    {
        throw "population should has individuals";
    }
    if (algorithmType != 0 && algorithmType != 1)
    {
        throw "only two types of algorithm";
    }
    if (minSigma < 0.0 || minSigma > 1.0)
    {
        throw "wrong min sigma";
    }
    if (maxSigma < 0.0 || maxSigma > 1.0)
    {
        throw "wrong max sigma";
    }
    setSize = 0;
    setMutationPropability(minSigma, maxSigma);
    addNewIndividuals(miValue);
    //wartosc prawd. mutacji domyslnie 1/2

}


void Population::generateNextPopulation()
{
    qDebug() << minSigma << maxSigma;
    //sortujemy wg. wsp. dopasowania
    vector<Square *> reproducers = selectionFunction(population, setSize, lambdaValue);
    random_shuffle(reproducers.begin(), reproducers.end());
    vector<Square *> children;
    for (unsigned int i = 0; 2 * i + 1 < min((size_t)lambdaValue, reproducers.size()) - min((size_t)lambdaValue, reproducers.size()) % 2; i++)
    {
        pair<Square*,Square*> result = reproductionFunction(reproducers.at(2 * i), reproducers.at(2 * i + 1));
        //z danym prawd. mutujemy dzieci
        if (rand() % 100 < (int)(result.first->mutationPropability*100))
            result.first = mutationFunction(result.first);
        if (rand() % 100 < (int)(result.second->mutationPropability*100))
            result.second = mutationFunction(result.second);
        children.push_back(result.first);
        children.push_back(result.second);
    }
    if(algorithmType == 1)
    {
        population.clear();
        setSize = 0;
    }
    for(Square * e : children){
        population.insert(e);
        setSize++;
    }
}

void Population::cutPopulationToSomeBest(unsigned int howMany)
{
    auto it = population.end();
    while(setSize > howMany)
    {

        it = population.end();
        --it;
        population.erase(it);
        setSize--;
    }
}



void Population::setMutationPropability(double minSigma, double maxSigma)
{
    this->minSigma = minSigma;
    this->maxSigma = maxSigma;
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
        //TODO poprawić
        temp = new Square(squareSize, fitnessFunction, (minSigma+maxSigma)/2);
        qDebug() << temp->mutationPropability;
        temp->randomFill();
        population.insert(temp);
        setSize++;
    }
}

int Population::countFitness(const Square *invid)
{
    return fitnessFunction(invid);
}

vector< pair<int, int> > Population::howManySpecificFitness()
{
    vector< pair<int,int> > result;
    int fitness, howMany;
    for (auto it = population.begin(); it != population.end(); )
    {
        fitness = (*it)->countFitness();
        howMany = 1;
        it++;
        while(it != population.end() && (*it)->countFitness() == fitness)
        {
            howMany++, it++;
        }
        result.push_back(make_pair(fitness, howMany));
    }
    return result;
}

vector< pair<int, pair<int, vector<int> > > > Population::getSomeBest(int howMany)
{
    vector< pair<int, pair<int, vector<int> > > > result;
    for(auto it = population.begin(); it != population.end() && howMany > 0; howMany--, it++)
    {
        vector< int > temp((*it)->getSize() * (*it)->getSize());
        for(unsigned int i = 0; i < (*it)->getSize(); ++i)
            for(unsigned int j = 0; j < (*it)->getSize(); ++j)
                temp[i*(*it)->getSize() + j] = (*it)->get(i, j);
        result.push_back(make_pair((*it)->id, make_pair((*it)->countFitness(), temp)));
    }
    return result;
}
