#include "VariableNeighborhoodSearch.h"

#define NB_NEIGHBORHOOD 5

using namespace std;
using namespace std::placeholders;

Solution VariableNeighborhoodSearch::shaking(Solution x, Solution (Neighborhood::*n_neighborhood)(Solution, int, int)) {
    random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> distr(0,x.getSize()-1);

    int a,b,t;

	a = distr(eng);
	do {
		b = distr(eng);
	} while (a == b);

    if (a > b) {
        t = b;
        b = a;
        a = t;
    }

    auto neighborhood = bind(n_neighborhood, Neighborhood(), _1, _2, _3);

    return neighborhood(x, a, b);
}

Solution VariableNeighborhoodSearch::run(Problem p, Solution x) {
    Solution x_neighbor;
    Solution x_optim = x;
    p.objective(x_optim);
    int k=1;

    Solution (Neighborhood::*neighborhood)(Solution, int, int);

    for (int i=0;i<10;i++) {
        if (k == 1) {
            neighborhood = &Neighborhood::swapMove;
        } else if (k == 2) {
            neighborhood = &Neighborhood::inversionMove;
        } else if (k == 3) {
            neighborhood = &Neighborhood::backwardInsertionMove;
        } else if (k == 4) {
            neighborhood = &Neighborhood::forwardInsertionMove;
        } else {
            neighborhood = &Neighborhood::scrambleMove;
        }

        x_neighbor = shaking(x, neighborhood);
        x_neighbor = LocalSearch().run(p, x_neighbor, neighborhood);

        if (x_neighbor.getEval() < x_optim.getEval()) {
            x_optim = x_neighbor;
            k = 0;
        }

        if (k < NB_NEIGHBORHOOD) {
            k++;
        } else {
            k = 1;
        }
    }

    return x_optim;
}
