#include "square.h"

int Square::number = 0;

int Square::placeInTable(unsigned int row, unsigned int column) const
{
    if (row >= size || column >= size)
        throw "out of range";
    return row*size + column;
}

Square::Square(unsigned int _size) : size(_size)
{
    values = new int[size*size];
    id = number++;
    for (unsigned int i = 1; i <= size*size; ++i)
    {
        values[i - 1] = 0;
    }
}


Square::Square(const Square &x)
{
    size = x.size;
    values = new int[size*size];
    id = number++;
    for (unsigned int i = 0; i < size*size; ++i)
        values[i] = x.values[i];
}

Square::Square(const Square *x)
{
    size = x->size;
    values = new int[size*size];
    id = number++;
    for (unsigned int i = 0; i < size*size; ++i)
        values[i] = x->values[i];
}

bool Square::operator==(const Square &x)
{
    for (unsigned int i = 0; i < size*size; ++i)
        if (values[i] != x.values[i])
            return false;
    return true;
}

Square::~Square()
{
    delete[] values;
}

const Square &Square::operator=(const Square &x)
{
    if(size != x.size)
        throw "diffrent sides sizes";
    if (&x == this)
        return x;
    for (unsigned int i = 0; i < size*size; ++i)
        values[i] = x.values[i];
    return x;
}

void Square::randomFill()
{
    for (unsigned int i = 1; i <= size*size; ++i)
    {
        values[i - 1] = i;
    }
    std::random_shuffle(values, values + size*size);
}

int Square::get(int row, int column) const
{
    if (values == 0)
        throw "access to not reserved memory";
    return values[placeInTable(row,column)];
}

void Square::set(unsigned int row, unsigned int column, int value)
{
    if (row >= size || column >= size)
        throw "out of range";
    values[row*size + column] = value;
}

void Square::swapValues(int valueA, int valueB)
{
    unsigned int whereA = size*size, whereB = size*size;
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

void Square::swapPoints(int ax, int ay, int bx, int by)
{
    swap(values[placeInTable(ax, ay)], values[placeInTable(bx, by)]);
}

bool Square::operator<(const Square &b) const
{
    if(size != b.size)
        throw "diffrent sides sizes";
    for (unsigned int i = 0; i < size; ++i)
    {
        for (unsigned int j = 0; j < size; ++j)
            if (get(i, j) != b.get(i, j))
                return get(i, j) < b.get(i, j);
    }
    return id < b.id;
}

unsigned int Square::getSize() const
{
    return size;
}


ostream &operator<<(ostream &os, const Square &square)
{
    os << square.getSize() << " x " << square.getSize() << "\n";
    for (unsigned int i = 0; i < square.getSize(); ++i)
    {
        for (unsigned int j = 0; j < square.getSize(); ++j)
            os << square.get(i, j) << " ";
        os << "\n";
    }
    return os;
}
