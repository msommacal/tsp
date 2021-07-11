#include "Algorithm.h"

using namespace std;

Algorithm::Algorithm() {}

vector<Solution> Algorithm::bruteforce(Problem p) {
    vector<Solution> x_optim;
    double min = numeric_limits<double>::infinity();

    Solution x({0,1,2,3,4});
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
