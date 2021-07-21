#include "LocalSearch.h"

using namespace std;

LocalSearch::LocalSearch() {}

Solution LocalSearch::run(Problem p, Solution x) {
    Solution x_neighbor;
    Solution x_optim = x;
    p.objective(x_optim);

    int a,b;
    for (a=0;a<x.getSize();a++) {
        for (b=a+1;b<x.getSize();b++) {
            x_neighbor = Neighborhood().swapMove(x, a, b);
            p.objective(x_neighbor);

            if (x_neighbor.getEval() < x_optim.getEval()) {
                x_optim = x_neighbor;
            }
        }
    }

    return x_optim;
}

Solution LocalSearch::run(Problem p, Solution x, vector<Solution> T) {
    Solution x_neighbor;
    Solution x_optim = x;
    p.objective(x_optim);

    int a,b;
    for (a=0;a<x.getSize();a++) {
        for (b=a+1;b<x.getSize();b++) {
            x_neighbor = Neighborhood().swapMove(x, a, b);
            p.objective(x_neighbor);

            int i = 0;
            while (i < T.size() && (T.at(i) != x_neighbor)) {
                i++;
            }

            if (i == T.size()) {
                if ((x_optim == x) || (x_neighbor.getEval() < x_optim.getEval())) {
                    x_optim = x_neighbor;
                }
            }
        }
    }

    return x_optim;
}
