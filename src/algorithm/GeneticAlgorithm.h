#ifndef GENETIC_ALGORITHM
#define GENETIC_ALGORITHM

#include <vector>
#include "../Problem.h"

class GeneticAlgorithm {
    private:

    std::vector<Solution> selection(Problem p, std::vector<Solution> pop, int mu);
    std::vector<Solution> crossover(Problem p, std::vector<Solution> parents);

    public:

    GeneticAlgorithm();

    Solution run(Problem p, int n, int mu);
};

#endif
