#include "Problem.h"

using namespace std;

Problem::Problem(vector<vector<double>> data)
  : m_data(data),
    m_size(data.size()) {}

Problem::Problem(string filename) {
    ifstream file(filename);
    vector<vector<double>> data;
    vector<double> line;

    int n;
    double v;

    file >> n;
    for (int i=0;i<n;i++) {
        line.clear();
        for (int j=0;j<n;j++) {
            file >> v;
            line.push_back(v);
        }
        data.push_back(line);
    }

    m_data = data;
    m_size = n;
}

Problem::~Problem() {
    // todo
}

vector<vector<double>> Problem::getData() {
    return m_data;
}

double Problem::getData(int i, int j) {
    return m_data.at(i).at(j);
}

int Problem::getSize() {
    return m_size;
}

double Problem::objective(Solution &x) {
    vector<int> x_data = x.getData();
    double cost = 0;
    int old = x_data.at(0);

    for (long unsigned int i=1;i<x_data.size();i++) {
        cost += m_data.at(old).at(x_data.at(i));
        old = x_data.at(i);
    }

    cost += m_data.at(old).at(x_data.at(0));

    x.setEval(cost);

    return cost;
}

// Solution Problem::solve(...);

void Problem::print() const {
    for (long unsigned int i=0;i<m_data.size();i++) {
        for (long unsigned int j=0;j<m_data.at(i).size();j++) {
            cout << m_data.at(i).at(j) << ' ';
        }
        cout << endl;
    }
}
