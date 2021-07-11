#ifndef NEIGHBORHOOD
#define NEIGHBORHOOD

#include <algorithm>
#include <random>
#include <vector>
#include "Solution.h"

class Neighborhood {
    public:

    Solution swapMove(Solution x, int a, int b);
    Solution inversionMove(Solution x, int a, int b);
    Solution scrambleMove(Solution x, int a, int b);
    Solution backwardInsertionMove(Solution x, int a, int b);
    Solution forwardInsertionMove(Solution x, int a, int b);
};
#endif
