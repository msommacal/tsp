#include "Algorithm.h"

#define KMAX 5

using namespace std;

Algorithm::Algorithm() {}

vector<Solution> Algorithm::bruteforce(Problem p) {
    vector<Solution> x_optim;
    double min = numeric_limits<double>::infinity();

    vector<int> x_data;
    for (int i=0;i<p.getSize();i++) {
        x_data.push_back(i);
    }

    Solution x(x_data);
    vector<int> s = x.getData();
    sort(s.begin(), s.end());
    do {
        x.setData(s);

        if (p.objective(x) <= min) {
            if (x.getEval() != min) {
                x_optim.clear();
            }
            x_optim.push_back(x);
            min = x.getEval();
        }
    } while(next_permutation(s.begin(), s.end()));

    return x_optim;
}

Solution Algorithm::localSearch(Problem p, Solution x) {
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

Solution Algorithm::localSearch(Problem p, Solution x, vector<Solution> T) {
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

double Algorithm::P(double T, Solution x, Solution y) {
	return exp(x.getEval()-y.getEval())/T;
}

double Algorithm::g(double T) {
	return 0.95*T;
}

Solution Algorithm::simulatedAnnealing(Problem p, Solution x) {
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

Solution Algorithm::shaking(Solution x, int k) {
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

Solution Algorithm::variableNeighborhoodSearch(Problem p, Solution x) {
    Solution x_neighbor;
    Solution x_optim = x;
    p.objective(x_optim);
    int k=1;

    for (int i=0;i<10;i++) {
        x_neighbor = shaking(x, k);
        x_neighbor = localSearch(p, x_neighbor);

        if (x_neighbor.getEval() < x_optim.getEval()) {
            x_optim = x_neighbor;
            k = 0;
        }

        if (k < KMAX) {
            k++;
        } else {
            k = 1;
        }
    }

    return x_optim;
}

Solution Algorithm::tabuSearch(Problem p, Solution x) {
    Solution x_init = x;
    Solution x_optim = x;
    p.objective(x_optim);
    vector<Solution> T;

    Solution x_neighbor;

    for (int i=0;i<5;i++) {
        x_neighbor = localSearch(p,x_init,T);
        if (x_neighbor.getEval() < x_optim.getEval()) {
            x_optim = x_neighbor;
        }
        x_init = x_neighbor;
        T.push_back(x_neighbor);
    }

    return x_optim;
}
