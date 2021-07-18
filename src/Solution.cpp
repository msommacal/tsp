#include "Solution.h"

using namespace std;

Solution::Solution() {}

Solution::Solution(int size) {
    random_device rd;
    default_random_engine rng(rd());

    vector<int> data;
    for (int i=0;i<size;i++) {
        data.push_back(i);
    }

    shuffle(data.begin(), data.end(), rng);

    m_data = data;
    m_eval = numeric_limits<double>::quiet_NaN();
    m_size = data.size();
}

Solution::Solution(vector<int> data)
  : m_data(data),
    m_eval(numeric_limits<double>::quiet_NaN()),
    m_size(data.size()) {}

Solution::~Solution() {
    // todo
}

vector<int> Solution::getData() const {
    return m_data;
}

int Solution::getData(int i) const {
    return m_data.at(i);
}

void Solution::setData(vector<int> data) {
    m_data = data;
    m_size = data.size();
}

void Solution::setData(int i, int value) {
    m_data.at(i) = value;
}

double Solution::getEval() const {
    return m_eval;
}

void Solution::setEval(double eval) {
    m_eval = eval;
}

int Solution::getSize() const {
    return m_size;
}

void Solution::print() {
    cout << m_eval << "\t";
    for (int i=0; i < m_data.size(); i++) {
        cout << m_data.at(i) << ' ';
    }
    cout << endl;
}

bool Solution::operator==(const Solution &an) const {
    return this->getData() == an.getData();
}

bool Solution::operator!=(const Solution &an) const {
    return this->getData() != an.getData();
}

bool Solution::operator<(const Solution& an) const {
    return m_eval < an.m_eval;
}
