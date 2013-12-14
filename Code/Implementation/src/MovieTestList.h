#ifndef MOVIETESTLIST_H
#define MOVIETESTLIST_H

using namespace std;

#include "MovieList.h"
#include <vector>
#include <map>

typedef map<int, MovieList*> movie_hashmap;

class MovieTestList
{
public:
    static MovieTestList* getInstance();

    void addMovie(const int &id, MovieList* p);
    movie_hashmap::iterator begin() {return _id_map.begin();}
    movie_hashmap::iterator end() {return _id_map.end();}

private:
    movie_hashmap _id_map;
    static void CleanUp();
    MovieTestList();
    ~MovieTestList(){}

    // Not Copyable:
    MovieTestList(MovieTestList const&);
    MovieTestList& operator = (MovieTestList const&);

    static MovieTestList* _instance;
};

#endif
