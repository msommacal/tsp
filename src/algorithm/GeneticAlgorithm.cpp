#include "GeneticAlgorithm.h"

using namespace std;

GeneticAlgorithm::GeneticAlgorithm() {}

vector<Solution> GeneticAlgorithm::selection(Problem p, vector<Solution> pop, int mu) {
    random_device rd;
    mt19937 eng(rd());
    vector<Solution> population = pop;
    vector<Solution> parents;
    vector<double> score;
    double sum = 0;
    double sum_score = 0;
    double r;

    for (int j=0;j<mu;j++) {
        for (int i=0;i<population.size();i++) {
            sum += population.at(i).getEval();
        }

        uniform_real_distribution<double> distr(0,population.size()-1);
        r = distr(eng);

        sum_score = 0;

        int i=-1;
        do {
            i++;
            sum_score += 1-population.at(i).getEval()/sum;
        } while (sum_score < r);

        parents.push_back(population.at(i));
        population.erase(population.begin()+i);
    }

    return parents;
}

vector<Solution> GeneticAlgorithm::crossover(Problem p, vector<Solution> parents) {
    random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> distr(1,parents.at(0).getSize()-2);
    vector<Solution> children;
    int r;

    for (int k=0;k<parents.size()/2;k++) {
        Solution child1(parents.at(2*k));
        Solution child2(parents.at(2*k+1));

        r = distr(eng);

        for (int i=0; i<r;i++) {
            child1.setData(i, parents.at(2*k+1).getData(i));
            child2.setData(i, parents.at(2*k).getData(i));
        }

        vector<int> child1_data;
        vector<int> child2_data;

        int i = 0;
        int j = 0;

        while (i < child1.getSize() && j < child2.getSize()) {
            child1_data = child1.getData();
            child2_data = child2.getData();

            while (i < child1.getSize() && find(child2_data.begin(), child2_data.end(), child1.getData(i)) != child2_data.end()) {
                i++;
            }
            while (j < child2.getSize() && find(child1_data.begin(), child1_data.end(), child2.getData(j)) != child1_data.end()) {
                j++;
            }

            if (i < child1.getSize() && j < child2.getSize()) {
                child1.setData(i, child2_data.at(j));
                child2.setData(j, child1_data.at(i));
            }
        }

        p.objective(child1);
        p.objective(child2);

        children.push_back(child1);
        children.push_back(child2);
    }

    return children;
}

Solution GeneticAlgorithm::run(Problem p, int n, int mu) {
    vector<Solution> population;

    for (int k=0;k<10;k++) {
        while (population.size() < n) {
            population.push_back(Solution(p.getSize()));
            p.objective(population.back());
        }

        vector<Solution> parents = selection(p, population, mu);

        vector<Solution> children = crossover(p, parents);

        population.insert(population.end(), children.begin(), children.end());

        sort(population.begin(), population.end());

        vector<Solution>::iterator ip;
        ip = unique(population.begin(), population.end());
        population.resize(distance(population.begin(), ip));

        if (population.size() > n) {
            population.erase(population.begin()+n, population.end());
        }
    }

    return population.at(0);
}
