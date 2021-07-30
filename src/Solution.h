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

    std::vector<int> getData() const;
    int getData(int i) const;
    void setData(std::vector<int> data);
    void setData(int i, int value);
    double getEval() const;
    void setEval(double eval);
    int getSize() const;

    void print() const;

    bool operator==(const Solution& an) const;
    bool operator!=(const Solution& an) const;
    bool operator<(const Solution& an) const;
};

#endif
