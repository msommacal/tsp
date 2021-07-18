#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "Algorithm.h"
#include "Neighborhood.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc == 1) {
        cerr << "Error: file argument is missing." << endl;
        exit(1);
    }

    // instantiate a problem
    Problem p(argv[1]);

    // Bruteforce
    //cout << "Bruteforce:" << endl;
    //vector<Solution> x_optim = Algorithm().bruteforce(p);
    //for (int i=0;i<x_optim.size();i++) {
    //    cout << "  ";
    //    x_optim.at(i).print();
    //}
    //cout << endl;

    // generate a random solution
    cout << "Initial solution:" << endl << "  ";
    Solution x(p.getSize());
    x.print();
    cout << endl;

    // Local Search
    cout << "Local Search:" << endl << "  ";
    Solution y1 = Algorithm().localSearch(p, x);
    y1.print();

    // Simulated Annealing
    cout << "Simulated Annealing:" << endl << "  ";
    Solution y2 = Algorithm().simulatedAnnealing(p, x);
    y2.print();

    // VNS
    cout << "Variable Neighborhood Search:" << endl << "  ";
    Solution y3 = Algorithm().variableNeighborhoodSearch(p, x);
    y3.print();

    // Tabu Search
    cout << "Tabu Search:" << endl << "  ";
    Solution y4 = Algorithm().tabuSearch(p, x);
    y4.print();

    // Genetic Algorithm
    cout << "Genetic Algorithm:" << endl << "  ";
    Solution y5 = Algorithm().geneticAlgorithm(p, 30, 8);
    y5.print();

    return 0;
}
