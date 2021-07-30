#ifndef PROBLEM
#define PROBLEM

#include <fstream>
#include <vector>
#include "Solution.h"

class Problem {
    private:

    std::vector<std::vector<double>> m_data;
    int m_size;

    public:

    Problem(std::vector<std::vector<double>> data);
    Problem(std::string filename);
    ~Problem();

    std::vector<std::vector<double>> getData();
    double getData(int i, int j);
    int getSize();

    double objective(Solution &x);
    //Solution solve();

    void print() const;
};

#endif
