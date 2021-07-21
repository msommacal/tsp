#ifndef TABU_SEARCH
#define TABU_SEARCH

#include <vector>
#include "../Problem.h"
#include "LocalSearch.h"

class TabuSearch {
    public:

    TabuSearch();

    Solution run(Problem p, Solution x);
};

#endif
