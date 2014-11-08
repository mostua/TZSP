#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <set>

using namespace std;



//class represents square containing numbers from 1 to n^2
template<unsigned int size>
class Square
{
protected:
	int * values;
public:
	Square()
	{
		values = new int[size*size];
		for (int i = 1; i <= size*size; ++i)
		{
			values[i - 1] = 0;
		}
	}
	//copy constructor
	Square(const Square& x) : Square()
	{
		for (int i = 0; i < size*size; ++i)
			values[i] = x.values[i];
	}
	/*const Square& operator=(const Square& x)
	{
		for (int i = 0; i < size*size; ++i)
			values[i] = x.values[i];
		return x;
	}*/
	//befor using method call srand(time(0)) to proper working
	void randomFill()
	{
		for (int i = 1; i <= size*size; ++i)
		{
			values[i - 1] = i;
		}
		random_shuffle(values, values + size*size);
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
ostream& operator<<(ostream & os, const Square<size> &square)
{
	os << size << " x " << size << "\n";
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			os << square.get(i, j) << " ";
		os << "\n";
	}
	return os;
}

//fitness function measure how square is far from being magic square
template<unsigned int size>
int fitnessFunction(Square<size>);

//function creates two children from two parents, mixing diagonals
template<unsigned int size>
pair<Square<size>, Square<size>> reproductionFunction(const Square<size> &, const Square<size> &);

//function swap 2 points in square
template<unsigned int size>
Square<size> mutationFunction(const Square<size> & square);

//we can sort squares comparing theirs fitness values
template<unsigned int size>
bool operator<(Square<size> a, Square<size> b)
{
	return fitnessFunction(a) < fitnessFunction(b);
}

//class contain whole population of squares
template<unsigned int size>
class Population
{
private:
	const int INF = 100000;
	const int maxIterations = 1000;
	const int pMutation = 1, qMutation = 5; //probability of mutation is pMutation/qMutation
protected:
	vector<Square<size>> population;
	
public:
	//make population with the size 
	Population(int begin_size) 
	{
		Square<size> temp;
		for (int i = 0; i < begin_size; ++i)
		{
			temp.randomFill();
			population.push_back(temp);
		}
	}
	//methos whil st
	Square<size> algorithm(int howManyReproduces)
	{
		for (int t = 1; t < maxIterations; ++t)
		{
			//make it works
			//sort(population.begin(), population.end(), [](int a, int b)->bool { return		fitnessFunction(a) < fitnessFunction(b); }());
			sort(population.begin(), population.end());
			if (population.size() > howManyReproduces)
				population.resize(howManyReproduces);
			//we assume that fitnessFunction returns 0 if we find magic square
			if (fitnessFunction(*population.begin()) == 0)
			{
				return *population.begin();
			}
			random_shuffle(population.begin(), population.end());
			int bestSquare = INF;
			for (size_t i = 0; i < population.size(); ++i)
			{
				bestSquare = min(bestSquare, fitnessFunction(population[i]));
				//cout << population[i] << endl;
			}
			//it's temporary solution to prints results on a screen
			cout << "it: " <<  t << " " << bestSquare << endl;
			pair<Square<size>, Square<size>> result;
			size_t populationSize = population.size();
			for (size_t i = 0; 2 * i + 1 < min((size_t)howManyReproduces, populationSize) - min((size_t)howManyReproduces, populationSize)%2; i++)
			{
				result = reproductionFunction(population[2 * i], population[2 * i + 1]);
				//one time on five mutate child
				if (rand() % qMutation < pMutation)
					result.first = mutationFunction(result.first);
				if (rand() % qMutation < pMutation)
					result.second = mutationFunction(result.second);
				population.push_back(result.first);
				population.push_back(result.second);
			}
			
		}
		return *population.begin();
	}
};

//function returns fitness of square measered as a sum of distances from befor calculated sum in row/column/diagonal to sum of every row, column and diagonal 
//see in code
template<unsigned int size>
int fitnessFunction(Square<size> square)
{
	int result = 0;
	int currentSumInRow, currentSumInCoumn, diagonalSum;
	int fitnessSum = size*(size * size + 1) / 2;
	for (int i = 0; i < size; ++i)
	{
		currentSumInRow = currentSumInCoumn = 0;
		//for each row and column sum values of littles squares
		for (int j = 0; j < size; ++j)
		{
			currentSumInRow += square.get(i, j); 
			currentSumInCoumn += square.get(j, i);
		}
		//sum results of absolut diffrance of sum calculated befor and sum in a row/column
		result += abs(fitnessSum - currentSumInRow) + abs(fitnessSum - currentSumInCoumn);
	}
	diagonalSum = 0;
	for (int i = 0; i < size; ++i)
	{
		diagonalSum += square.get(i,i);
	}
	result += abs(fitnessSum - diagonalSum);

	diagonalSum = 0;
	for (int i = 0; i < size; ++i)
	{
		diagonalSum += square.get(i, size - i - 1);
	}
	result += abs(fitnessSum - diagonalSum);
	return result;
}

//reproduction function creates descendants
template<unsigned int size>
pair<Square<size>, Square<size>> reproductionFunction(const Square<size> & parentA, const Square<size> & parentB)
{
	//if (parentA.getSize() != parentB.getSize())
	//	throw "Sheep can't reproduce with human";
	//make one of children with parentA diagonals, and second with parentB diagonals
	//copy child A from parent A and so for child B
	Square<size> childA(parentA), childB(parentB);
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

//Mutation function swaping two random points in 
template<unsigned int size>
Square<size> mutationFunction(const Square<size> & square)
{
	Square<size> result(square);
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


int main()
{
	srand((unsigned int)(time(NULL)));
	Population<4> population(1000);
	/*Square<3> a, b;
	//a.randomFill();
	a.randomFill();
	//b.randomFill();
	b.randomFill();
	cout << a << endl;
	cout << b << endl;
	pair<Square<3>, Square<3>> children;
	children = reproductionFunction(a, b);
	cout << children.first << endl;
	cout << children.second << endl;*/
	
	Square<4> result = population.algorithm(100);
	cout << "Result: fitness = " << fitnessFunction(result) << endl;
	cout << result << endl;
	system("pause");
}