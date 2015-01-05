#include "selection.h"


vector<Square *> selection::rankingSelection(set<Square *, Square::cmp> candidates, unsigned int setSize, unsigned int howMany)
{
    vector<Square *> result;
    while(result.size() < howMany)
    {
        int i = 0;
        for(auto it = candidates.begin(); it != candidates.end() &&  result.size() != howMany; ++it, ++i)
        {
            if((rand() % setSize) < (setSize - i - 1))
            {
                result.push_back(*it);
            }
        }
    }
    return result;
}


vector< Square *> selection::ruleteSelection(set<Square *, Square::cmp> candidates, unsigned int setSize, unsigned int howMany)
{
    vector<Square *> result;
    while(result.size() < howMany)
    {
        int i = 0;
        for(auto it = candidates.begin(); it != candidates.end() &&  result.size() != howMany; ++it, ++i)
        {
            if(double(rand() % 100)/100.0 < 1 - double((*it)->countFitness() - (*candidates.begin())->countFitness()) / double((*candidates.begin())->countFitness()))
            {
                result.push_back(*it);
            }
        }
    }
    return result;
}


vector<Square *> selection::bestSelection(set<Square *, Square::cmp> candidates, unsigned int setSize, unsigned int howMany)
{
    vector<Square *> result;
    while(result.size() < howMany)
    {
        int i = 0;
        for(auto it = candidates.begin(); it != candidates.end() &&  result.size() != howMany; ++it, ++i)
        {
            result.push_back(*it);
        }
    }
    return result;
}
