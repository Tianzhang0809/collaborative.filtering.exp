#ifndef MOVIEMOVIESIMNORM_H
#define MOVIEMOVIESIMNORM_H

#include "MovieMovieSim.h"

class MovieMovieSimNorm : public MovieMovieSim{
public:
	MovieMovieSimNorm(string &url, const int &k): MovieMovieSim(url,k),_u(0.95){}
protected:
	virtual float getScore(const int &user_id, const int &movie_id);
	virtual float handleScore(float score, float var1, float var2);
	virtual vector<ScorePair>* getRatingList(const int &user_id, const int &movie_id);
	float _u;

};

#endif
