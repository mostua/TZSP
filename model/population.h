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
    int algorithmType; //0 - lambda + mi, 1 - lambda, mi
public:
    /*!
     * \brief Population tworzy populacje o zadanej wielkoscia, nastepnie wskazniki na funkcje odpowiadajace (odpowiednio) za mutacje, dopasowanie, reprodukcje
     */
    Population(int, int , Square*(*mut)(const Square*), int(*fit)(const Square*), pair< Square*, Square *>(*repr)(const Square *, const Square *));
    /*!
     * \brief generateNextPopulation metoda iteruje do nastepnej populacji, howManyReproduces - ile sie rozmnaz
     * \param howManyReproduces
     */
    void generateNextPopulation(unsigned int howManyReproduces);
    /*!
     * \brief setMutationPropability metoda iteruje do nastepnej populacji, howManyReproduces - ile sie rozmnaz
     * \param p licznik
     * \param q mianownik
     */
	void setMutationPropability(int p, int q);
    /*!
     * \brief getPopulationSize
     * \return wielkość populacji
     */
	unsigned int getPopulationSize();
    /*!
     * \brief getBest
     * \return najlepszy osobnik
     */
    Square getBest();
    /*!
     * \brief populationAverage
     * \return średnie przystosowanie populacji
     */
    double populationAverage();
    /*!
     * \brief addNewIndividuals  metoda doloswuje nowych osobnikow
     * \param howMany liczba dolosowanych
     */
	void addNewIndividuals(int howMany);
    /*!
     * \brief countFitness metoda zwraca przystosowanie osobnika z wykorzystaniem funkcji przystosowania podanej w konstruktorze
     * \param invid kwadrat mierzony
     * \return przystosowanie mierzane funkcja z konstruktora
     */
    int countFitness(const Square *invid);
};



#endif
