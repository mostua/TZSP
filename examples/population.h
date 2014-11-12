#ifndef _POPULATION_H
#define _POPULATION_H

#include "square.h"
#include <vector>

//class contain whole population of squares
template<unsigned int size>
class Population
{
private:
	const int INF = 100000;
	int pMutation, qMutation; //probability of mutation is pMutation/qMutation
protected:
    vector< Square<size> > population;
public:
	//make population with the size 
	Population(int begin_size);
	//methos whil st
	void generateNextPopulation(int howManyReproduces, bool(*cmp)(const Square<size>&, const Square<size>&), Square<size>(*mutationFunction)(const Square<size>&), int(*fitnessFunction)(const Square<size>&), pair< Square<size>,Square<size> > (*reproductionFunction)(const Square<size> &, const Square<size> &));
	void setMutationPropability(int p, int q);
	unsigned int getPopulationSize();
	Square<size> getBest(int(*fitnessFunction)(const Square<size>&));
};


template<unsigned int size>
Population<size>::Population(int begin_size)
{
	Square<size> temp;
	if (begin_size <= 0)
	{
		throw "population should has individuals";
	}
	for (int i = 0; i < begin_size; ++i)
	{
		temp.randomFill();
		population.push_back(temp);
	}
	//default value of mutation propability is 50%
	setMutationPropability(1, 2);
}

template<unsigned int size>
void Population<size>::generateNextPopulation(int howManyReproduces, bool(*cmp)(const Square<size>&, const Square<size>&), Square<size>(*mutationFunction)(const Square<size>&), int(*fitnessFunction)(const Square<size>&), pair<Square<size>, Square<size>> (*reproductionFunction)(const Square<size> &, const Square<size> &))
{
	//we get best individuals 
	sort(population.begin(), population.end(), cmp);
	if (population.size() > howManyReproduces)
		population.resize(howManyReproduces);
	population.shrink_to_fit();
	//we want to random parents reproduction
	random_shuffle(population.begin(), population.end());
	pair<Square<size>, Square<size>> result;
	size_t populationSize = population.size();
	for (size_t i = 0; 2 * i + 1 < min((size_t)howManyReproduces, populationSize) - min((size_t)howManyReproduces, populationSize) % 2; i++)
	{
		result = reproductionFunction(population.at(2 * i), population.at(2 * i + 1));
		//one time on five mutate child
		if (rand() % qMutation < pMutation)
			result.first = mutationFunction(result.first);
		if (rand() % qMutation < pMutation)
			result.second = mutationFunction(result.second);
		population.push_back(result.first);
		population.push_back(result.second);

	}
}


template<unsigned int size>
void Population<size>::setMutationPropability(int p, int q)
{
	pMutation = p;
	qMutation = q;
}

template<unsigned int size>
unsigned int Population<size>::getPopulationSize()
{
	return population.size();
}

template<unsigned int size>
Square<size> Population<size>::getBest(int(*fitnessFunction)(const Square<size>&))
{
	size_t best = 0;
	for (size_t i = 1; i < population.size(); ++i)
	{
		if (fitnessFunction(population[i]) < fitnessFunction(population[best]))
			best = i;
	}
	return population[best];
}

#endif
