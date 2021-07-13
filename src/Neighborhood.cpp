#include "Neighborhood.h"

using namespace std;

Solution Neighborhood::swapMove(Solution x, int a, int b) {
    Solution x_neighbor(x);

    x_neighbor.setData(a, x.getData(b));
    x_neighbor.setData(b, x.getData(a));

    return x_neighbor;
}

Solution Neighborhood::inversionMove(Solution x, int a, int b) {
    Solution x_neighbor(x);

    for (int i=a;i<=b;i++) {
        x_neighbor.setData(i, x.getData((b+a)-i));
    }

    return x_neighbor;
}

Solution Neighborhood::scrambleMove(Solution x, int a, int b) {
    random_device rd;
    default_random_engine rng(rd());

    Solution x_neighbor(x);
    vector<int> x_data = x.getData();
    vector<int> x_data_sub {x_data.begin()+a, x_data.begin()+b+1};

    shuffle(x_data_sub.begin(), x_data_sub.end(), rng);

    for (int i=a;i<=b;i++) {
        x_neighbor.setData(i, x_data_sub.at(i-a));
    }

    return x_neighbor;
}

Solution Neighborhood::backwardInsertionMove(Solution x, int a, int b) {
    Solution x_neighbor(x);

    for (int i=a;i<b;i++) {
        x_neighbor.setData(i, x.getData(i+1));
    }

    x_neighbor.setData(b, x.getData(a));

    return x_neighbor;
}

Solution Neighborhood::forwardInsertionMove(Solution x, int a, int b) {
    Solution x_neighbor(x);

    x_neighbor.setData(a, x.getData(b));

    for (int i=a+1;i<=b;i++) {
        x_neighbor.setData(i, x.getData(i-1));
    }

    return x_neighbor;
}
