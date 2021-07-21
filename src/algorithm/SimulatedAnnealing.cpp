#include "SimulatedAnnealing.h"

using namespace std;

SimulatedAnnealing::SimulatedAnnealing() {}

double SimulatedAnnealing::P(double T, Solution x, Solution y) {
	return exp(x.getEval()-y.getEval())/T;
}

double SimulatedAnnealing::g(double T) {
	return 0.95*T;
}

Solution SimulatedAnnealing::run(Problem p, Solution x) {
    Solution x_neighbor;
    Solution x_optim = x;
    p.objective(x_optim);

    double T = 10000;
    double r;
    int a,b;

    for (int k=0;k<50;k++) {
        random_device rd;
	    mt19937 eng(rd());
		uniform_int_distribution<int> distr(0,p.getSize()-1);

		a = distr(eng);
		do {
			b = distr(eng);
		} while (a == b);

		if (a < b) {
			x_neighbor = Neighborhood().swapMove(x_optim, a, b);
		} else {
			x_neighbor = Neighborhood().swapMove(x_optim, b, a);
		}

        if (p.objective(x_neighbor) < x_optim.getEval()) {
            x_optim = x_neighbor;
        } else {
            uniform_real_distribution<double> distr2(0,1);
		    r = distr2(eng);

		    if (r < P(T, x_optim, x_neighbor)) {
			    x_optim = x_neighbor;
		    }

            T = g(T);
        }
    }

    return x_optim;
}
