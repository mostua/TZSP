#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <algorithm>  
using namespace std;


/*!
 * \brief The Square class repezentuje kwadrat
 */
class Square
{
private:

    /*!
     * \brief placeInTable funkcja zwraca miejsce w tablicy dla danej pozycji
     * \param row wiersz
     * \param column kolumna
     * \return  numer w tablicy values
     */
    int placeInTable(unsigned int row, unsigned int column) const;
    int(*fitnessFunction)(const Square *);
protected:
	int * values;
public:
	int id;
	static int number;
    unsigned int size;
    double mutationPropability;
    Square(unsigned int size, int(*fitnessFunction)(const Square *), double mutationPropability = 0.0f);
    //konstruktor kopiujacy wersja referencyjna
    Square(const Square& x);
    //konstruktor kopiujacy wersja pointerowa
    Square(const Square * x);
    bool operator==(const Square& x);
    ~Square();
    const Square& operator=(const Square& x);
	//do poprawnego dzialania winien byc wywolany srand(time(0));
    void randomFill();
	//zwraca wartosc z pola magicznego kwadrata z danej kolumny i wiersza, liczymy wiersze i kolumny od 0
    int get(int row, int column) const;
	//ustaw wartosc w danej kolumnie i wierszu
    void set(unsigned int row, unsigned int column, int value);
	//zamien miejscami dwie wartosci
    void swapValues(int valueA, int valueB);
	//zamien miejscami dwa punktu
    void swapPoints(int ax, int ay, int bx, int by);
	//porownanie przez rozszerzenie porownania na na kolejne wartosci, najpierw porownujemy wartosci [0][0], poznmiej [0][1] etc.
    int countFitness() const;
    bool operator<(const Square& b) const;
    unsigned int getSize() const;
    friend ostream& operator<<(ostream &, const Square &);
    struct cmp
    {
        bool operator()(const Square * a, const Square * b)
        {
            if(a->countFitness() != b->countFitness())
            {
                return a->countFitness() < b->countFitness();
            }
            return a->id < b->id;
        }
    };
};


//f. do wyswietlania kwadrata na standardowe wyjscie.

ostream& operator<<(ostream & os, const Square &square);


#endif


