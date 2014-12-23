#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <algorithm>  
using namespace std;


/* Było wczesniej templatem, ale komplikowalo to niepotrzebnie niektore rzeczy */
class Square
{
private:
	//funkcja zwraca miejsce w tablicy dla danej pozycji
    int placeInTable(unsigned int row, unsigned int column) const;

protected:
	int * values;

public:
	int id;
	static int number;
    unsigned int size;
    Square(unsigned int size);
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
    bool operator<(const Square& b) const;

    unsigned int getSize() const;

    friend ostream& operator<<(ostream &, const Square &);
};



//f. do wyswietlania kwadrata na standardowe wyjscie.

ostream& operator<<(ostream & os, const Square &square);


#endif


