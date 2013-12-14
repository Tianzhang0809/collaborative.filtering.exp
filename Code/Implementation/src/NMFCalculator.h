#ifndef NMFCALCULATOR_H
#define NMFCALCULATOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <algorithm>
#include <math.h>
#include <stdio.h>
#include "MovieDictionary.h"
#include "UserDictionary.h"
#include "MovieList.h"
#include "UserList.h"
#include "ScorePair.h"
#include "SimCache.h"

class NMFCalculator
{
public:
    NMFCalculator(const int k);
    void calculate(ostream &out);

private:
    int _k;

    MovieDictionary* _movieDict;
    UserDictionary* _userDict;
    SimCache*       _cache;

};

#endif
