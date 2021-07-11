#include "Solution.h"

using namespace std;

Solution::Solution(vector<int> data)
  : m_data(data),
    m_eval(numeric_limits<double>::quiet_NaN()) {}

Solution::~Solution() {
    // todo
}

vector<int> Solution::getData() {
    return m_data;
}

double Solution::getData(int i) {
    return m_data.at(i);
}

void Solution::setData(vector<int> data) {
    m_data = data;
}

void Solution::setData(int i, int value) {
    m_data.at(i) = value;
}

double Solution::getEval() {
    return m_eval;
}

void Solution::setEval(double eval) {
    m_eval = eval;
}

void Solution::print() {
    cout << m_eval << "\t";
    for (int i=0; i < m_data.size(); i++) {
        cout << m_data.at(i) << ' ';
    }
    cout << endl;
}
