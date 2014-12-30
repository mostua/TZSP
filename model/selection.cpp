#include "selection.h"


vector<Square *> selection::rankingSelection(vector<Square *> candidates, unsigned int how_many, int (*fitnessFunction)(const Square *))
{
    vector<Square *> result;
    sort(candidates.begin(), candidates.end(), [fitnessFunction](const Square *a, const Square *b)->bool{ 	return (fitnessFunction(a) != fitnessFunction(b) ? fitnessFunction(a) < fitnessFunction(b) : a < b);  });
    while(result.size() < how_many)
    {
        for(size_t i = 0; i < candidates.size() &&  result.size() != how_many; ++i)
        {
            if((rand() % candidates.size()) < (candidates.size() - i - 1))
            {
                result.push_back(candidates[i]);
            }
        }
    }
    return result;
}

vector<Square *> selection::ruleteSelection(vector<Square *> candidates, unsigned int how_many, int (*fitnessFunction)(const Square *))
{
    vector<Square *> result;
    sort(candidates.begin(), candidates.end(), [fitnessFunction](const Square *a, const Square *b)->bool{ 	return (fitnessFunction(a) != fitnessFunction(b) ? fitnessFunction(a) < fitnessFunction(b) : a < b);  });
    while(result.size() < how_many)
    {
        for(size_t i = 0; i < candidates.size() &&  result.size() != how_many; ++i)
        {
            if((rand() % candidates.size()) < (candidates.size() - i - 1))
            {
                result.push_back(candidates[i]);
            }
        }
    }
    return result;
}
