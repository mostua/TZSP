#ifndef POPULATION_H
#define POPULATION_H

#include "square.h"
#include <algorithm>
#include <vector>
using namespace std;

//klasa kontener, zawiera populacje
class Population
{
protected:
    int squareSize;
	const int INF = 100000;
	int pMutation, qMutation; //prawdopodbienstwo mutacji postaci p/q
    vector< Square* > population;
    Square* (*mutationFunction)(const Square *);
    int(*fitnessFunction)(const Square *);
    pair< Square*, Square*>(*reproductionFunction)(const Square *, const Square *);
public:
	//konstruktor, tworzy populacje o zadanej wielkoscia, nastepnie wskazniki na funkcje odpowiadajace (odpowiednio) za mutacje, dopasowanie, reprodukcje
    Population(int, int , Square*(*mut)(const Square*), int(*fit)(const Square*), pair< Square*, Square *>(*repr)(const Square *, const Square *));
	//metoda iteruje do nastepnej populacji, howManyReproduces - ile sie rozmnaz
    void generateNextPopulation(unsigned int howManyReproduces);
	//metoda ustawia prawd. mutacji
	void setMutationPropability(int p, int q);
	//metoda zwraca wielkosc populacji
	unsigned int getPopulationSize();
	//metoda zwraca najlepszego osobnika
    Square getBest();
	//metoda zwraca srednia dopasowania
    double populationAverage();
	//metoda doloswuje nowych osobnikow
	void addNewIndividuals(int howMany);
    //metoda zwraca przystosowanie osobnika z wykorzystaniem funkcji przystosowania podanej w konstruktorze
    int countFitness(const Square *invid);

};



#endif
