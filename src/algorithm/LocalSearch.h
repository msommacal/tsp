#ifndef LOCAL_SEARCH
#define LOCAL_SEARCH

#include <vector>
#include "../Problem.h"
#include "../Neighborhood.h"

class LocalSearch {
    public:

    LocalSearch();

    Solution run(Problem p, Solution x);
    Solution run(Problem p, Solution x, std::vector<Solution> T);
};

#endif
