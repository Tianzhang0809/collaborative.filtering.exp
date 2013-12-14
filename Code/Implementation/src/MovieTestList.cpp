#include "MovieTestList.h"

// Singleton Implementation:
MovieTestList* MovieTestList::_instance = 0;
MovieTestList::MovieTestList(){ atexit(&CleanUp);}
void MovieTestList::CleanUp(){ delete _instance; _instance = 0;}
MovieTestList* MovieTestList::getInstance()
{
    if (_instance == 0)
        _instance = new MovieTestList();
    return _instance;
}

// add operation
void MovieTestList::addMovie(const int &id, MovieList* p)
{
    _id_map.insert(pair<int, MovieList*> (id, p));
}
