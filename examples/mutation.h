#include "square.h"



//przestrzen nazw zawierajaca wszystkie funkcje mutacji
namespace mutation
{
	//mutacja zmieniajace dwa punkty miedzy sob¹
	template<unsigned int size>
	Square<size> swapToPoints(const Square<size> & square)
	{
		Square<size> result = square;
		int ax, ay, av, bx, by, bv;
		ax = rand() % size;
		ay = rand() % size;
		av = result.get(ay, ax);
		bx = rand() % size;
		by = rand() % size;
		bv = result.get(by, bx);
		result.set(by, bx, av);
		result.set(ay, ax, bv);
		return result;
	}
	//mutacja zmieniajace dwie kolumny miedzy soba
	template<unsigned int size>
	Square<size> swapToColumns(const Square<size> & square)
	{
		Square<size> result = square;
		int columna, columnb;
		//losujemy sposrod 3 kolumn
		vector<int> tab({ 0, 1, 2 });
		random_shuffle(tab.begin(), tab.end());
		columna = tab[0], columnb = tab[1];
		for (int i = 0; i < size; ++i)
		{
			result.swapPoints(columna, i, columnb, i);
		}
		return result;
	}
	//mutacja zmieniajaca dwa wierszy miedzy soba
	template<unsigned int size>
	Square<size> swapToRows(const Square<size> & square)
	{
		Square<size> result = square;
		int rowa, rowb;
		//losujemy sposrod 3 wierszy
		vector<int> tab({ 0, 1, 2 });
		random_shuffle(tab.begin(), tab.end());
		rowa = tab[0], rowb = tab[1];
		for (int i = 0; i < size; ++i)
		{
			result.swapPoints(i, rowa, i, rowb);
		}
		return result;
	}
}