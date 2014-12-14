#ifndef _SQUARE_H
#define _SQUARE_H

#include <iostream>
#include <algorithm>  
using namespace std;

//klasa odzwierciedla magiczny kwadrat
template<unsigned int size>
class Square
{
private:
	//funkcja zwraca miejsce w tablicy dla danej pozycji
    int placeInTable(unsigned int row, unsigned int column) const
	{
		if (row >= size || column >= size)
			throw "out of range";
		return row*size + column;
	}
protected:
	int * values;

public:
	int id;
	static int number;
	Square()
	{
		values = new int[size*size];
		id = number++;
        for (unsigned int i = 1; i <= size*size; ++i)
		{
			values[i - 1] = 0;
		}
	}
	//konstruktor kopiujacy
	Square(const Square& x)
	{
		values = new int[size*size];
		id = number++;
        for (unsigned int i = 0; i < size*size; ++i)
			values[i] = x.values[i];
	}
	bool operator==(const Square& x)
	{
		for (int i = 0; i < size*size; ++i)
			if (values[i] != x.values[i])
				return false;
		return true;
	}
	~Square()
	{
		delete[] values;
	}
	const Square& operator=(const Square& x)
	{
		if (&x == this)
			return x;
        for (unsigned int i = 0; i < size*size; ++i)
			values[i] = x.values[i];
		return x;
	}
	//do poprawnego dzialania winien byc wywolany srand(time(0));
	void randomFill()
	{
        for (unsigned int i = 1; i <= size*size; ++i)
		{
			values[i - 1] = i;
		}
		std::random_shuffle(values, values + size*size);
	}
	//zwraca wartosc z pola magicznego kwadrata z danej kolumny i wiersza, liczymy wiersze i kolumny od 0
	int get(int row, int column) const
	{
		if (values == 0)
			throw "access to not reserved memory";
		return values[placeInTable(row,column)];
	}
	//ustaw wartosc w danej kolumnie i wierszu
    void set(unsigned int row, unsigned int column, int value)
	{
		if (row >= size || column >= size)
			throw "out of range";
		values[row*size + column] = value;
	}
	//zamien miejscami dwie wartosci
	void swapValues(int valueA, int valueB)
	{
		int whereA = size*size, whereB = size*size;
        for (unsigned int i = 0; i < size*size; ++i)
		{
			if (values[i] == valueA)
			{
				whereA = i;
			}
			if (values[i] == valueB)
			{
				whereB = i;
			}
		}
		if (whereA == size*size || whereB == size*size)
		{
			throw "cant find value";
		}
		std::swap(values[whereA], values[whereB]);

	}
	//zamien miejscami dwa punktu
	void swapPoints(int ax, int ay, int bx, int by)
	{
		swap(values[placeInTable(ax, ay)], values[placeInTable(bx, by)]);
	}
	//porownanie przez rozszerzenie porownania na na kolejne wartosci, najpierw porownujemy wartosci [0][0], poznmiej [0][1] etc.
	bool operator<(const Square<size>& b) const
	{
        for (unsigned int i = 0; i < size; ++i)
		{
            for (unsigned int j = 0; j < size; ++j)
				if (get(i, j) != b.get(i, j))
					return get(i, j) < b.get(i, j);
		}
		return id < b.id;
	}

	template<unsigned int size2>
	friend ostream& operator<<(ostream &, const Square<size2> &);
};

template<unsigned int size>
int Square<size>::number = 0;

//f. do wyswietlania kwadrata na standardowe wyjscie.
template<unsigned int size>
ostream& operator<<(ostream & os, const Square<size> &square)
{
	os << size << " x " << size << "\n";
    for (unsigned int i = 0; i < size; ++i)
	{
        for (unsigned int j = 0; j < size; ++j)
			os << square.get(i, j) << " ";
		os << "\n";
	}
	return os;
}


#endif
