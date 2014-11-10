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

#endif
