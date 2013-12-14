#ifndef REGSIM_H
#define REGSIM_H

#include "MovieMovieSimNorm.h"

class RegSim : public MovieMovieSimNorm{
public:
    // Constructor
    RegSim(string &s, const int &k): MovieMovieSimNorm(s, k)
                                     _permute_set()
                                     _lambda(0.1)
                                     _maxIt(100)
                                     _t0(1)
                                     _alpha(0.5)
                                     _beta(0.8)
    {}

protected:
    virtual float getScore(const int &user_id, const int &movie_id);

private:
    set <int> _permute_set;
    float _lambda;
    int _maxIt;
    float _t0;
    float _alpha;
    float _beta;
    void permute(const int &user_id, const int &movie_id);
    float computeSim(vector<ScorePair>* a, vector<ScorePair>* b);
};

#endif
