#include "Bruteforce.h"

using namespace std;

Bruteforce::Bruteforce() {}

vector<Solution> Bruteforce::run(Problem p) {
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
