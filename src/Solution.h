#ifndef SOLUTION
#define SOLUTION

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

class Solution {
    private:

    std::vector<int> m_data;
    double m_eval;
    int m_size;

    public:

    Solution();
    Solution(int size);
    Solution(std::vector<int> data);
    ~Solution();

    std::vector<int> getData();
    double getData(int i);
    void setData(std::vector<int> data);
    void setData(int i, int value);
    double getEval();
    void setEval(double eval);
    int getSize();

    void print();
};

#endif
