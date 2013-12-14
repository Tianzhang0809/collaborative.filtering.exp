#include "RegSim.h"
#include "math.h"

float RegSim::getScore(const int &user_id, const int &movie_id)
{
    
    vector<ScorePair>* sim_list = permute(user_id, movie_id);
    vector<ScorePair>* rating_list=this->getRatingList(user_id,movie_id);
    vector<ScorePair>::iterator sim_it=sim_list->begin();
    vector<ScorePair>::iterator rating_it=rating_list->begin();
    int sid;
    int rid;
    float weight=0;
    float score=0;
    while (sim_it!=sim_list->end() && rating_it!=rating_list->end()){
            sid = sim_it->id;
            rid = rating_it->id;
            if (sid==rid){
                    score+=sim_it->score*rating_it->score;
                    weight+=sim_it->score;
                    sim_it++;
                    rating_it++;
            }else if (sid<rid){
                    sim_it++;
            }else{
                    rating_it++;
            }
    }
    if (weight == 0) 
        score = 0;
    else
        score /= weight;
    
    //UserList* owner=_userDict->getUser(user_id);
    MovieList* owner = _movieDict->getMovie(movie_id);
    
    //score=score*owner->var()+owner->avg();
    score += _u*owner->avg()+(1-_u)*3.38029;
    return score;
}

float RegSim::computeSim(vector<ScorePair>* a, vector<ScorePair>* b, int style)
{
    vector<ScorePair>::iterator i = a -> begin();
    vector<ScorePair>::iterator j = b -> begin();
    float score = 0;
    while (i != a -> end() && j != b -> end()){
        if (i -> id < j -> id){
            i++;
        }else if (i -> id > j -> id){
            j++;
        }else{
            if (style == 0)
                score += (i->score)*(j->score);
            else
                score += (i->score_norm)*(j->score_norm);
            i++;
            j++;
        }
    }
    return score;
}

vector<ScorePair>* RegSim::permute(const int &user_id, const int &movie_id)
{
    int pk = getPK(user_id, movie_id);
    // If precalculatd
    if (_permute_map.find(pk) != _permute_map.end()){
        return _permute_map.find(pk) -> second;
    }

    // f'(b) = X'Xb + 2lambda*b - X'y    
    // X'y: score attribute
    vector<ScorePair>* Xty = this -> getSimList(user_id, movie_id);
    vector<ScorePair>* y = this -> getFirstList(user_id, movie_id);
    vector<ScorePair>* b;

    int it = 0;
    while (it < _maxIt){
        float norm = 0;
        for (int i = 0; i != Xty -> size(); ++i){
            if (it == 0){
                // init
                ScorePair pair;
                pair.id = (*Xty)[i].id; 
                pair.score = (double) rand() / (RAND_MAX);
                b -> push_back(pair);
            }else{
                // train a regression
                ScorePair p = (*y)[i];
                float gd = 2*_lambda*(*b)[i].score - (*Xty)[i].score;
                int oid = (*Xty)[i].id;
                vector<ScorePair>* XiSims;
                if (pk == movie_id){
                    XiSims = this -> getSimList(user_id, (*Xty)[i].id);
                }else{
                    XiSims = this -> getSimList((*Xty)[i].id, movie_id);
                }
                for (int k = 0; k != b -> size(); ++k){
                    gd += (*XiSims)[k].score * (*b)[k].score;
                }
                //  b = b - t/k * f'(b);
                (*b)[i] -= _t/k*gd;
            }
            norm += (*b)[i]*(*b)[i];
        }
        // normalize b
        norm = sqrt(norm);
        for (int i = 0; i != b -> size(); ++i){
            (*b)[i] /= norm;
        }
        it ++;
    }

    _permute_map.insert(primary_key, b);
    return b;
}
 
