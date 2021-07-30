#ifndef ANT_COLONY_OPTIMIZATION
#define ANT_COLONY_OPTIMIZATION

#include <algorithm>
#include <vector>
#include "../Problem.h"
#include "../Neighborhood.h"

class Ant {
    private:

    std::vector<int> m_path;
    std::vector<int> m_remaining_points;
    double m_eval;

    public:

    Ant(Problem p);
    ~Ant();

    double getEval() const;
    int getPosition() const;
    std::vector<int> getPath() const;
    std::vector<int> getRemainingPoints() const;

    void evaluate(Problem p);
    void move(int position);

    void print() const;

    bool operator<(const Ant& an) const;
};

class AntColonyOptimization {
    private:

    double m_alpha;
    double m_beta;
    double m_rho;
    double m_Q;

    std::vector<double> probability(Problem p, Ant ant, std::vector<std::vector<double>> pheromones);
    void tour(Problem p, Ant& ant, std::vector<std::vector<double>> pheromones);
    void update(Problem p, Ant ant, std::vector<std::vector<double>>& pheromones);

    public:

    AntColonyOptimization(double alpha=1, double beta=5, double rho=0.5, double Q=100);

    double getAlpha() const;
    double getBeta() const;
    double getRho() const;
    double getQ() const;

    Solution run(Problem p, int n);
};

#endif
