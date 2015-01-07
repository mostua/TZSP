#ifndef SELECTION_H
#define SELECTION_H

#include "square.h"
#include <vector>
#include <set>
using namespace std;

namespace selection
{
    typedef  vector< Square *> (*selectionFunction)(set<Square *, Square::cmp>, unsigned int, unsigned int);
    vector< Square *> rankingSelection(set<Square *, Square::cmp> candidates, unsigned int setSize, unsigned int howMany);
    vector< Square *> ruleteSelection(set<Square *, Square::cmp> candidates, unsigned int setSize, unsigned int how_many);
    vector< Square *> bestSelection(set<Square *, Square::cmp> candidates, unsigned int setSize, unsigned int how_many);
}

#endif // SELECTION_H
