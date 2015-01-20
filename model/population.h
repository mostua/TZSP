#ifndef POPULATION_H
#define POPULATION_H

#include "square.h"
#include <algorithm>
#include <vector>
#include <set>
#include <QDebug>
using namespace std;

/*!
 * \brief The Population class zawiera populacje oraz udostepnia podstawowe metody na niej
 */
class Population
{

protected:
    /*!
     * \brief squareSize rozmiar kwadratu jaki przechowuje populacja
     */
    unsigned int squareSize;
    /*!
     * \brief miValue wartość początkowa populacji
     */
    unsigned int miValue;
    /*!
     * \brief lambdaValue liczba rozmnażających się
     */
    unsigned int lambdaValue;
	const int INF = 100000;
    double minSigma, maxSigma;
    /*!
     * \brief population set przechowuje populacje posortowana według funkcji przystosowania, każde dodanie osobników powinno wiązać się z naprawieniem posortowania
     */
    set< Square*, Square::cmp> population;

    /*!
     * \brief setSize rozmiar populacji
     */
    unsigned int setSize;
    /*!
     * Wskażnik na funkcje mutacji
     */
    Square* (*mutationFunction)(const Square *);
    /*!
     * Wskaźnik na funkcje przystowania
     */
    int(*fitnessFunction)(const Square *);
    /*!
     * Wskaźnik na funkcje reprodukcji
     */
    pair< Square*, Square*>(*reproductionFunction)(const Square *, const Square *);
    /*!
     * Wskaźnik na funkcje selekcji
     */
    vector< Square *> (*selectionFunction)(set<Square *, Square::cmp>, unsigned int, unsigned int);
    /*!
     * \brief algorithmType typ symulacji, aktualnie nie użytywany
     */
    int algorithmType; //0 - lambda + mi, 1 - lambda, mi
public:
    /*!
     * \brief Population tworzy populacje o zadanej wielkoscia, nastepnie wskazniki na funkcje odpowiadajace (odpowiednio) za mutacje, dopasowanie, reprodukcje
     */
    Population(unsigned int squareSize, unsigned int miValue, unsigned int lambdaValue, double minSigma, double maxSigma, Square*(*mutationFunction)(const Square*), int(*fitnessFunction)(const Square*), vector< Square *> (*selectionFunction)(set<Square *, Square::cmp>, unsigned int, unsigned int), pair< Square*, Square* >(*reproductionFunction)(const Square *, const Square *), int _algorithmType);
    /*!
     *
     */
    ~Population();

    /*!
     * \brief generateNextPopulation metoda iteruje do nastepnej populacji
     */
    void generateNextPopulation();
    /*!
     *
     */
    void cutPopulationToSomeBest(unsigned int howMany);
    /*!
     * \brief setMutationPropability metoda iteruje do nastepnej populacji
     * \param p licznik
     * \param q mianownik
     */
    void setMutationPropability(double minSigma, double maxSigma);
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
    /*!
     * \brief howManySpecificFitness metoda liczy ile jest osobnikow o danym przystosowaniu
     * \return wektor par (przystosowanie, liczba osobników, która ma to przystosowanie)
     */
    vector<pair<int,int>> howManySpecificFitness();
    /*!
     * \brief getSomeBest metoda zwraca x najlepszych osobnikow
     * \param howMany jest xem
     * \return vector najlepszych osobnikow
     */
    vector< pair<int, pair<int, vector<int> > > > getSomeBest(int howMany);
};



#endif
