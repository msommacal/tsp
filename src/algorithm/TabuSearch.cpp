#include "TabuSearch.h"

using namespace std;

TabuSearch::TabuSearch() {}

Solution TabuSearch::run(Problem p, Solution x, Solution (Neighborhood::*neighborhood)(Solution, int, int)) {
    Solution x_init = x;
    Solution x_optim = x;
    p.objective(x_optim);
    vector<Solution> T;

    Solution x_neighbor;

    for (int i=0;i<5;i++) {
        x_neighbor = LocalSearch().run(p,x_init,neighborhood,T);
        if (x_neighbor.getEval() < x_optim.getEval()) {
            x_optim = x_neighbor;
        }
        x_init = x_neighbor;
        T.push_back(x_neighbor);
    }

    return x_optim;
}
