#include <algorithm>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>

#include "algorithm/Bruteforce.h"
#include "algorithm/LocalSearch.h"
#include "algorithm/SimulatedAnnealing.h"
#include "algorithm/VariableNeighborhoodSearch.h"
#include "algorithm/TabuSearch.h"
#include "algorithm/GeneticAlgorithm.h"
#include "algorithm/AntColonyOptimization.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc == 1) {
        cerr << "Error: arguments are missing." << endl;
        exit(1);
    }

    int i = 1;
    string filename = "";
    while (i<argc && filename == "") {
        if (argv[i][0] != '-') {
            filename = argv[i];
        }
        i++;
    }

    if (filename == "") {
        cerr << "Error: file argument is missing." << endl;
        exit(2);
    }

    Problem p(filename);

    // generate a random solution
    Solution x(p.getSize());

    vector<string> all_methods = {"--bf", "--vns", "--ts", "--sa", "--ga", "--ls", "--aco"};
    vector<string> methods;
    if (argc == 2) {
        methods = all_methods;
    } else {
        for (int j=1;j<argc;j++) {
            if (j != i-1) {
                methods.push_back(argv[j]);
            }
        }
    }

    for (int i=0;i<methods.size();i++) {
        if (methods.at(i).compare("--bf") == 0) {
            cout << "Bruteforce:" << endl;
            vector<Solution> x_optim = Bruteforce().run(p);
            for (int i=0;i<x_optim.size();i++) {
                cout << "  ";
                x_optim.at(i).print();
            }
        } else if (methods.at(i).compare("--vns") == 0) {
            cout << "Variable Neighborhood Search:" << endl << "  ";
            Solution y3 = VariableNeighborhoodSearch().run(p, x);
            y3.print();
        } else if (methods.at(i).compare("--ls") == 0) {
            cout << "Local Search:" << endl << "  ";
            Solution y1 = LocalSearch().run(p, x);
            y1.print();
        } else if (methods.at(i).compare("--sa") == 0) {
            cout << "Simulated Annealing:" << endl << "  ";
            Solution y2 = SimulatedAnnealing().run(p, x);
            y2.print();
        } else if (methods.at(i).compare("--ga") == 0) {
            cout << "Genetic Algorithm:" << endl << "  ";
            Solution y5 = GeneticAlgorithm().run(p, 30, 8);
            y5.print();
        } else if (methods.at(i).compare("--ts") == 0) {
            cout << "Tabu Search:" << endl << "  ";
            Solution y4 = TabuSearch().run(p, x);
            y4.print();
        } else if (methods.at(i).compare("--aco") == 0) {
            cout << "Ant Colony Optimization:" << endl << "  ";
            Solution y6 = AntColonyOptimization().run(p, 10);
            y6.print();
        } else {
            cerr << "Error: " << methods.at(i) << " is not a valid method." << endl;
        }
    }

    return 0;
}
