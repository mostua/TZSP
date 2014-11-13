#include "square.h"



//namespaces with reproduction functions
namespace reproduction
{  
  //reproduction function creates descendants
  template<unsigned int size>
  pair<Square<size>, Square<size>> reproductionFunction(const Square<size> & parentA, const Square<size> & parentB)
  {
	  //if (parentA.getSize() != parentB.getSize())
	  //	throw "Sheep can't reproduce with human";
	  //make one of children with parentA diagonals, and second with parentB diagonals
	  //copy child A from parent A and so for child B
	  Square<size> childA, childB;
	  childA = parentA, childB = parentB;
	  //swap (x,x) in childA to value of parentB (x,x) same to (n-x-1, x)
	  int x, y;
	  for (int i = 0; i < size; ++i)
	  {
		  x = childA.get(i, i);
		  y = parentB.get(i, i);
		  childA.swap(x, y);
	  }
	  for (int i = 0; i < size; ++i)
	  {
		  if (size % 2 == 1 && size / 2 == i)
			  continue;
		  x = childA.get(size - i - 1, i);
		  y = parentB.get(size - i - 1, i);
		  childA.swap(x, y);
	  }
	  for (int i = 0; i < size; ++i)
	  {
		  x = childB.get(i, i);
		  y = parentA.get(i, i);
		  childB.swap(x, y);
	  }
	  for (int i = 0; i < size; ++i)
	  {
		  if (size % 2 == 1 && size / 2 == i)
			  continue;
		  x = childB.get(size - i - 1, i);
		  y = parentA.get(size - i - 1, i);
		  childB.swap(x, y);
	  }
	  //return reproduces childs
	  pair<Square<size>, Square<size>> result = make_pair(childA, childB);
	  return result;
  }
}