#ifndef SOLUTION
#define SOLUTION

#include <limits>
#include <iostream>
#include <vector>

class Solution {
    private:

    std::vector<int> m_data;
    double m_eval;

    public:

    Solution(std::vector<int> data);
    ~Solution();

    std::vector<int> getData();
    double getData(int i);
    void setData(std::vector<int> data);
    void setData(int i, int value);
    double getEval();
    void setEval(double eval);

    void print();
};

#endif
