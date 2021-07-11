#ifndef PROBLEM
#define PROBLEM

#include <vector>
#include "Solution.h"

class Problem {
    private:

    std::vector<std::vector<double>> m_data;

    public:

    Problem(std::vector<std::vector<double>> data);
    ~Problem();

    std::vector<std::vector<double>> getData();

    double objective(Solution &x);
    //Solution solve();

    void print() const;
};

#endif
