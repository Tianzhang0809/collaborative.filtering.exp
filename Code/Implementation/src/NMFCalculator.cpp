#include "NMFCalculator.h"
#include "MovieTestList.h"
#include <math.h>

// Constructor
NMFCalculator::NMFCalculator(const int k):
    _k(k)
{
    _movieDict = MovieDictionary::getInstance();
    _userDict = UserDictionary::getInstance();
    _cache = SimCache::getInstance();
}

void NMFCalculator::calculate(ostream &out)
{

}
