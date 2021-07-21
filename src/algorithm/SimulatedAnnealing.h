#ifndef SIMULATED_ANNEALING
#define SIMULATED_ANNEALING

#include <vector>
#include "../Problem.h"
#include "../Neighborhood.h"

class SimulatedAnnealing {
    private:

    double P(double T, Solution x, Solution y);
    double g(double T);

    public:

    SimulatedAnnealing();

    Solution run(Problem p, Solution x);

};

#endif
