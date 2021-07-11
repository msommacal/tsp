#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "Algorithm.h"
#include "Neighborhood.h"

using namespace std;

/**
 * \brief Petite fonction
 */
void printVector(vector<Solution> s) {
    for (int i=0;i<s.size();i++) {
        s.at(i).print();
    }
}

int main() {
    vector<vector<double>> data {
        {0,  20, 25, 30, 40, 35},
        {20,  0, 10, 15, 40, 50},
        {25, 10,  0, 30, 40, 35},
        {30, 15, 30,  0, 25, 30},
        {40, 40, 40, 25,  0, 15},
        {35, 50, 35, 30, 15,  0}
    };

    Problem p(data);

    Solution x({1,3,2,4,0});

    vector<Solution> x_opti = Algorithm().bruteforce(p);

    //temp(x_opti);

    Solution x_n = Neighborhood().scrambleMove(x, 1, 3);

    x.print();
    x_n.print();

    //Algorithm a;

    //a.bruteforce(p);

    //p.solve(x);

    //x.print();

    //Solution x = p.solve(x_init);

    //p.print();

    //delete &p;

    //Problem p(data);
    //Solution x = p.solve();

    //x.print();

    return 0;
}
