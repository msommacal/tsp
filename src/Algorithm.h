#ifndef ALGORITHM
#define ALGORITHM

#include <algorithm>
#include <vector>
#include "Neighborhood.h"
#include "Problem.h"

#include <iostream>

class Algorithm {
    private:

    double P(double T, Solution x, Solution y);
    double g(double T);
    Solution shaking(Solution x, int k);

    public:

    Algorithm();

    std::vector<Solution> bruteforce(Problem p);
    Solution localSearch(Problem p, Solution x);
    Solution localSearch(Problem p, Solution x, std::vector<Solution> T);
    Solution simulatedAnnealing(Problem p, Solution x);
    Solution variableNeighborhoodSearch(Problem p, Solution x);
    Solution tabuSearch(Problem p, Solution x);
    Solution geneticAlgorithm(Problem p, int n, int mu);
};

#endif
