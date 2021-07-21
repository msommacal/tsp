#ifndef VARIABLE_NEIGHBORHOOD_SEARCH
#define VARIABLE_NEIGHBORHOOD_SEARCH

#include <vector>
#include "../Problem.h"
#include "../Neighborhood.h"
#include "LocalSearch.h"

class VariableNeighborhoodSearch {
    private:

    Solution shaking(Solution x, int k);

    public:

    VariableNeighborhoodSearch() {}

    Solution run(Problem p, Solution x);
};

#endif
