#include "AntColonyOptimization.h"

#define PH_INIT 0.01

using namespace std;

AntColonyOptimization::AntColonyOptimization(double alpha, double beta, double rho, double Q) {
    m_alpha = alpha;
    m_beta = beta;
    m_rho = rho;
    m_Q = Q;
}

double AntColonyOptimization::getAlpha() const {
    return m_alpha;
}

double AntColonyOptimization::getBeta() const {
    return m_beta;
}

double AntColonyOptimization::getRho() const {
    return m_rho;
}

double AntColonyOptimization::getQ() const {
    return m_Q;
}

vector<vector<double>> initialization(Problem p) {
    vector<vector<double>> pheromones;
    vector<double> row;
    for(int i=0;i<p.getSize();i++){
		for(int j=0;j<p.getSize();j++){
			if (i != j) {
				row.push_back(PH_INIT);
            } else {
				row.push_back(0);
            }
		}
        pheromones.push_back(row);
        row.clear();
	}

    return pheromones;
}

vector<double> AntColonyOptimization::probability(Problem p, Ant ant, vector<vector<double>> pheromones) {
    vector<double> probabilities;
    vector<int> remaining_points = ant.getRemainingPoints();
    int i = ant.getPosition();
    int j;

    double d = 0;

    for (int l=0;l<remaining_points.size();l++) {
        j = remaining_points[l];
        probabilities.push_back(pow(pheromones.at(i).at(j), getAlpha())
                              * pow(1/p.getData(i,j), getBeta()));
        d += probabilities.back();
    }

    for (int l=0;l<probabilities.size();l++) {
        probabilities.at(l) /= d;
    }

    return probabilities;
}

void AntColonyOptimization::update(Problem p, Ant ant, vector<vector<double>>& pheromones) {
    vector<int> path = ant.getPath();
    double d = getQ()/ant.getEval();
    int i,j;

    for (int k=1;k<path.size();k++) {
        i = path.at(k-1);
        j = path.at(k);
        pheromones.at(i).at(j) += d;
    }

    pheromones.at(path.back()).at(path.at(0)) += d;
}

void AntColonyOptimization::tour(Problem p, Ant& ant, vector<vector<double>> pheromones) {
    random_device rd;
    mt19937 eng(rd());
    vector<double> probabilities;
    int index;
    double sum;
    double r;

    while (ant.getRemainingPoints().size() > 0) {
        uniform_real_distribution<double> distr(0,1);
        r = distr(eng);

        probabilities = probability(p, ant, pheromones);

        sum = 0;
        index = -1;
        do {
            index++;
            sum += probabilities.at(index);
        } while(sum < r);

        ant.move(ant.getRemainingPoints().at(index));
        probabilities.clear();
    }
}

Solution AntColonyOptimization::run(Problem p, int n) {
    Solution x_optim;
    Ant a_optim(p);

    vector<vector<double>> pheromones = initialization(p);

    vector<Ant> ants;

    for (int k=0;k<10;k++) {
        for (int i=0;i<n;i++) {
            ants.push_back(Ant(p));
            tour(p, ants.at(i), pheromones);
            ants.at(i).evaluate(p);
        }

        for (int i=0;i<n;i++) {
            update(p, ants.at(i), pheromones);
        }

        Ant a_min = *min_element(ants.begin(), ants.end());

        if (a_optim.getPath().size() == 1 || a_min.getEval() < a_optim.getEval()) {
            a_optim = a_min;
        }

        ants.clear();
    }

    x_optim.setData(a_optim.getPath());
    x_optim.setEval(a_optim.getEval());

    return x_optim;
}

Ant::Ant(Problem p) {
    random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> distr(0,p.getSize()-1);

    for (int i=0;i<p.getSize();i++) {
        m_remaining_points.push_back(i);
    }

    move(distr(eng));

    m_eval = numeric_limits<double>::quiet_NaN();
}

Ant::~Ant() {}

double Ant::getEval() const {
    return m_eval;
}

int Ant::getPosition() const {
    return m_path.back();
}

vector<int> Ant::getPath() const {
    return m_path;
}

vector<int> Ant::getRemainingPoints() const {
    return m_remaining_points;
}

void Ant::evaluate(Problem p) {
    Solution x(m_path);
    p.objective(x);
    m_eval = x.getEval();
}

void Ant::move(int position) {
    m_path.push_back(position);
    m_remaining_points.erase(remove(m_remaining_points.begin(),m_remaining_points.end(), position), m_remaining_points.end());
}

void Ant::print() const {
    vector<int> path = getPath();
    vector<int> remaining_points = getRemainingPoints();

    cout << m_eval << "\t";

    for (int i=0;i<path.size();i++) {
        cout << path.at(i) << " ";
    }
    cout << "\t\t";

    for (int i=0;i<remaining_points.size();i++) {
        cout << remaining_points.at(i) << " ";
    }
    cout << endl;
}

bool Ant::operator<(const Ant& an) const {
    return m_eval < an.m_eval;
}
