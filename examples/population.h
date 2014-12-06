#ifndef _POPULATION_H
#define _POPULATION_H

#include "square.h"
#include <vector>

//klasa kontener, zawiera populacje
template<unsigned int size>
class Population
{
protected:
	const int INF = 100000;
	int pMutation, qMutation; //prawdopodbienstwo mutacji postaci p/q
    vector< Square<size> > population;
	Square<size> (*mutationFunction)(const Square<size>&);
	int(*fitnessFunction)(const Square<size>&);
	pair< Square<size>, Square<size> >(*reproductionFunction)(const Square<size> &, const Square<size> &);
public:
	//konstruktor, tworzy populacje o zadanej wielkoscia, nastepnie wskazniki na funkcje odpowiadajace (odpowiednio) za mutacje, dopasowanie, reprodukcje
	Population(int , Square<size>(*mut)(const Square<size>&), int(*fit)(const Square<size>&), pair< Square<size>, Square<size> >(*repr)(const Square<size> &, const Square<size> &));
	//metoda iteruje do nastepnej populacji, howManyReproduces - ile sie rozmnaz
	void generateNextPopulation(int howManyReproduces);
	//metoda ustawia prawd. mutacji
	void setMutationPropability(int p, int q);
	//metoda zwraca wielkosc populacji
	unsigned int getPopulationSize();
	//metoda zwraca najlepszego osobnika
	Square<size> getBest(int(*fitnessFunction)(const Square<size>&));
	//metoda zwraca srednia dopasowania
	double populationAverage(int(*fitnessFunction)(const Square<size>&));
	//metoda doloswuje nowych osobnikow
	void addNewIndividuals(int howMany);

};


template<unsigned int size>
Population<size>::Population(int beginSize, Square<size>(*mutationFunction)(const Square<size>&), int(*fitnessFunction)(const Square<size>&), pair< Square<size>, Square<size> >(*reproductionFunction)(const Square<size> &, const Square<size> &)) : mutationFunction(mutationFunction), fitnessFunction(fitnessFunction), reproductionFunction(reproductionFunction)
{

	if (beginSize <= 0)
	{
		throw "population should has individuals";
	}
	addNewIndividuals(beginSize);
	//wartosc prawd. mutacji domyslnie 1/2
	setMutationPropability(1, 2);
}

template<unsigned int size>
void Population<size>::generateNextPopulation(int howManyReproduces)
{
	//sortujemy wg. wsp. dopasowania
	sort(population.begin(), population.end(), [this](const Square<size> &a, const Square<size> &b)->bool{ 	return (fitnessFunction(a) != fitnessFunction(b) ? fitnessFunction(a) < fitnessFunction(b) : a < b);  });
	if (population.size() > howManyReproduces)
		population.resize(howManyReproduces);
	population.shrink_to_fit();
	//z tych co sie beda dopasowywac wybieramy losowo rodzicow
	random_shuffle(population.begin(), population.end());
	pair<Square<size>, Square<size>> result;
	size_t populationSize = population.size();
	for (size_t i = 0; 2 * i + 1 < min((size_t)howManyReproduces, populationSize) - min((size_t)howManyReproduces, populationSize) % 2; i++)
	{
		result = reproductionFunction(population.at(2 * i), population.at(2 * i + 1));
		//z danym prawd. mutujemy dzieci
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

template < unsigned int size >
double Population<size>::populationAverage(int (*fitnessFunction)(const Square<size>&))
{
	long long sum = 0;
	for (size_t i = 0; i < population.size(); ++i)
	{
		sum += fitnessFunction(population[i]);
	}
	return ((double)sum) / population.size();

}

template <unsigned int size >
void Population<size>::addNewIndividuals(int howMany)
{
	Square<size> temp;
	if (howMany <= 0)
		throw "wrong number of new individuals";
	for (int i = 0; i < howMany; ++i)
	{
		temp.randomFill();
		population.push_back(temp);
	}
}
#endif
