#include "VariableNeighborhoodSearch.h"

#define NB_NEIGHBORHOOD 5

using namespace std;

Solution VariableNeighborhoodSearch::shaking(Solution x, int k) {
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

    if (k == 1) {
       return Neighborhood().swapMove(x, a, b);
    } else if (k == 2) {
       return Neighborhood().inversionMove(x, a, b);
    } else if (k == 3) {
       return Neighborhood().backwardInsertionMove(x, a, b);
    } else if (k == 4) {
       return Neighborhood().forwardInsertionMove(x, a, b);
    } else {
       return Neighborhood().scrambleMove(x, a, b);
    }
}

Solution VariableNeighborhoodSearch::run(Problem p, Solution x) {
    Solution x_neighbor;
    Solution x_optim = x;
    p.objective(x_optim);
    int k=1;

    for (int i=0;i<10;i++) {
        x_neighbor = shaking(x, k);
        x_neighbor = LocalSearch().run(p, x_neighbor);

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
