#ifndef PROBLEM
#define PROBLEM

#include <fstream>
#include <vector>
#include "Solution.h"

class Problem {
    private:

    std::vector<std::vector<double>> m_data;

    public:

    Problem(std::vector<std::vector<double>> data);
    Problem(std::string filename);
    ~Problem();

    std::vector<std::vector<double>> getData();

    double objective(Solution &x);
    //Solution solve();

    void print() const;
};

#endif
