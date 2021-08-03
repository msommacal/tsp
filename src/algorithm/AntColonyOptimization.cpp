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

vector<vector<double>> AntColonyOptimization::initialization(Problem p) {
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

void AntColonyOptimization::update(Ant ant, vector<vector<double>>& pheromones) {
    vector<int> data = ant.getData();
    double d = getQ()/ant.getEval();
    int i,j;

    for (int k=1;k<data.size();k++) {
        i = data.at(k-1);
        j = data.at(k);
        pheromones.at(i).at(j) += d;
    }

    pheromones.at(data.back()).at(data.at(0)) += d;
}

void AntColonyOptimization::tour(Problem p, Ant &ant, vector<vector<double>> pheromones) {
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
    Ant x_optim, a_min;

    vector<vector<double>> pheromones = initialization(p);

    vector<Ant> ants;

    for (int k=0;k<10;k++) {
        for (int i=0;i<n;i++) {
            ants.push_back(Ant(p.getSize()));
            tour(p, ants.at(i), pheromones);
            p.objective(ants.at(i));
        }

        for (int i=0;i<n;i++) {
            update(ants.at(i), pheromones);
        }

        a_min = *min_element(ants.begin(), ants.end());

        if (x_optim.getSize() == 0 || a_min.getEval() < x_optim.getEval()) {
            x_optim = a_min;
        }

        ants.clear();
    }

    return x_optim;
}

Ant::Ant() {
    m_size = 0;
    m_eval = numeric_limits<double>::quiet_NaN();
}

Ant::Ant(int size) {
    random_device rd;
	mt19937 eng(rd());
	uniform_int_distribution<int> distr(0,size-1);

    for (int i=0;i<size;i++) {
        m_remaining_points.push_back(i);
    }

    move(distr(eng));

    m_eval = numeric_limits<double>::quiet_NaN();

    m_size = 0;
}

void Ant::move(int position) {
    m_data.push_back(position);
    m_remaining_points.erase(remove(m_remaining_points.begin(),m_remaining_points.end(), position), m_remaining_points.end());
    m_size++;
}

int Ant::getPosition() const {
    return m_data.back();
}

vector<int> Ant::getRemainingPoints() const {
    return m_remaining_points;
}

void Ant::print() const {
    cout << m_eval << "\t";

    for (int i=0;i<m_data.size();i++) {
        cout << m_data.at(i) << " ";
    }
    cout << "\t";

    for (int i=0;i<m_remaining_points.size();i++) {
        cout << m_remaining_points.at(i) << " ";
    }
    cout << endl;
}
