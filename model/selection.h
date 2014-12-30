#ifndef SELECTION_H
#define SELECTION_H

#include "square.h"
#include <vector>
#include <set>
using namespace std;

namespace selection
{
    typedef  vector< Square *> (*selectionFunction)(vector<Square *>, unsigned int, int (*fitnessFunction)(const Square *));
    vector< Square *> rankingSelection(vector<Square *> candidates, unsigned int howMany, int (*fitnessFunction)(const Square *));
    vector< Square *> ruleteSelection(vector<Square *> candidates, unsigned int how_many, int (*fitnessFunction)(const Square *));
}

#endif // SELECTION_H
