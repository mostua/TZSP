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
    unsigned int squareSize;
    unsigned int miValue;
    unsigned int lambdaValue;
	const int INF = 100000;
	int pMutation, qMutation; //prawdopodbienstwo mutacji postaci p/q
    vector< Square* > population;
    Square* (*mutationFunction)(const Square *);
    int(*fitnessFunction)(const Square *);
    pair< Square*, Square*>(*reproductionFunction)(const Square *, const Square *);
    vector< Square *> (*selectionFunction)(vector<Square *>, unsigned int, int (*fitnessFunction)(const Square *));
    int algorithmType; //0 - lambda + mi, 1 - lambda, mi
public:
    /*!
     * \brief Population tworzy populacje o zadanej wielkoscia, nastepnie wskazniki na funkcje odpowiadajace (odpowiednio) za mutacje, dopasowanie, reprodukcje
     */
    Population(unsigned int squareSize, unsigned int miValue, unsigned int lambdaValue, Square*(*mutationFunction)(const Square*), int(*fitnessFunction)(const Square*), vector< Square *> (*selectionFunction)(vector<Square *>, unsigned int, int (*fitnessFunction)(const Square *)), pair< Square*, Square* >(*reproductionFunction)(const Square *, const Square *));
    /*!
     * \brief generateNextPopulation metoda iteruje do nastepnej populacji
     */
    void generateNextPopulation();
    /*!
     * \brief setMutationPropability metoda iteruje do nastepnej populacji
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
    * \brief getIndividual
    * \return i-ty osobnik
    */
    Square getIndividual(unsigned int which);
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
