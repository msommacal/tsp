#include "Problem.h"

using namespace std;

Problem::Problem(vector<vector<double>> data)
  : m_data(data) {}

Problem::~Problem() {
    // todo
}

double Problem::objective(Solution &x) {
    vector<int> x_data = x.getData();
    double cost = 0;
    int old = x_data.at(0);

    for (int i=1; i < x_data.size(); i++) {
        cost += m_data.at(old).at(x_data.at(i));
        old = x_data.at(i);
    }

    cost += m_data.at(old).at(x_data.at(0));

    x.setEval(cost);

    return cost;
}

// Solution Problem::solve(...);

void Problem::print() const {
    for (int i=0; i < m_data.size(); i++) {
        for (int j=0; j < m_data.at(i).size(); j++) {
            cout << m_data.at(i).at(j) << ' ';
        }
        cout << endl;
    }
}
