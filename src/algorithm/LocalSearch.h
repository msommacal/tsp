#ifndef LOCAL_SEARCH
#define LOCAL_SEARCH

#include <functional>
#include <vector>
#include "../Problem.h"
#include "../Neighborhood.h"

class LocalSearch {
    public:

    LocalSearch();

    Solution run(Problem p, Solution x, Solution (Neighborhood::*neighborhood)(Solution, int, int));
    Solution run(Problem p, Solution x, Solution (Neighborhood::*neighborhood)(Solution, int, int), std::vector<Solution> T);
};

#endif
