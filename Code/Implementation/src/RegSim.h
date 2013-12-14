#ifndef REGSIM_H
#define REGSIM_H

#include "MovieMovieSimNorm.h"

class RegSim : public MovieMovieSimNorm
{
public:
    // Constructor
    RegSim(string &s, const int &k): MovieMovieSimNorm(s, k){};

protected:
    virtual float getScore(const int &user_id, const int &movie_id);

private:
    map<int, vector<ScorePair>*> _permute_map;
    vector<ScorePair>* permute(const int &user_id, const int &movie_id);
};

#endif
