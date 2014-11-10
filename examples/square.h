#ifndef _SQUARE_H
#define _SQUARE_H

#include <iostream>
#include <algorithm>  
using namespace std;

//class represents square containing numbers from 1 to n^2
template<unsigned int size>
class Square
{
protected:
	int * values;

public:
	int id;
	static int number;
	Square()
	{
		values = new int[size*size];
		id = number++;
		for (int i = 1; i <= size*size; ++i)
		{
			values[i - 1] = 0;
		}
	}
	//copy constructor
	Square(const Square& x)
	{
		values = new int[size*size];
		id = number++;
		for (int i = 0; i < size*size; ++i)
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
		for (int i = 0; i < size*size; ++i)
			values[i] = x.values[i];
		return x;
	}
	//befor using method call srand(time(0)) to proper working
	void randomFill()
	{
		for (int i = 1; i <= size*size; ++i)
		{
			values[i - 1] = i;
		}
		std::random_shuffle(values, values + size*size);
	}
	//returns value at specific row and column counting from 0 to size - 1
	int get(int row, int column) const
	{
		if (row >= size || column >= size)
			throw "out of range";
		if (values == 0)
			throw "access to not reserved memory";
		return values[row*size + column];
	}
	//set value on specific row
	void set(int row, int column, int value)
	{
		if (row >= size || column >= size)
			throw "out of range";
		values[row*size + column] = value;
	}
	//swap places of to values
	void swap(int valueA, int valueB)
	{
		int whereA = size*size, whereB = size*size;
		for (int i = 0; i < size*size; ++i)
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
	template<unsigned int size2>
	friend ostream& operator<<(ostream &, const Square<size2> &);
};

template<unsigned int size>
int Square<size>::number = 0;

#endif