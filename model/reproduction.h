#ifndef REPRODUCTION_H
#define REPRODUCTION_H
#include "square.h"



//przestrzen nazw zawierajaca funkcje reprodukcji
namespace reproduction
{
	//funkcja zwraca pare dzieci

    pair<Square*, Square*> reproductionFunction(const Square* parentA, const Square* parentB);
}

#endif
