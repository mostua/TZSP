#include "square.h"



//namespaces with reproduction functions
namespace mutation
{
	//Mutation function swaping two random points in 
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

}