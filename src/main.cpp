#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#include "algorithm/Bruteforce.h"
#include "algorithm/LocalSearch.h"
#include "algorithm/SimulatedAnnealing.h"
#include "algorithm/VariableNeighborhoodSearch.h"
#include "algorithm/TabuSearch.h"
#include "algorithm/GeneticAlgorithm.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc == 1) {
        cerr << "Error: file argument is missing." << endl;
        exit(1);
    }

    // instantiate a problem
    Problem p(argv[1]);

    // Bruteforce
    cout << "Bruteforce:" << endl;
    vector<Solution> x_optim = Bruteforce().run(p);
    for (int i=0;i<x_optim.size();i++) {
        cout << "  ";
        x_optim.at(i).print();
    }
    cout << endl;

    // generate a random solution
    cout << "Initial solution:" << endl << "  ";
    Solution x(p.getSize());
    x.print();
    cout << endl;

    // Local Search
    cout << "Local Search:" << endl << "  ";
    Solution y1 = LocalSearch().run(p, x);
    y1.print();

    // Simulated Annealing
    cout << "Simulated Annealing:" << endl << "  ";
    Solution y2 = SimulatedAnnealing().run(p, x);
    y2.print();

    // VNS
    cout << "Variable Neighborhood Search:" << endl << "  ";
    Solution y3 = VariableNeighborhoodSearch().run(p, x);
    y3.print();

    // Tabu Search
    cout << "Tabu Search:" << endl << "  ";
    Solution y4 = TabuSearch().run(p, x);
    y4.print();

    // Genetic Algorithm
    cout << "Genetic Algorithm:" << endl << "  ";
    Solution y5 = GeneticAlgorithm().run(p, 30, 8);
    y5.print();

    return 0;
}
