# Traveller Salesman Problem

This project is a collection of optimization algorithms to solve the traveling salesman problem. However, it is also possible to adapt it for other problems such as the backpacking problem.

![Screenshot](img/screenshot.png?raw=true "Screenshot")

Thus, the following algorithms are implemented:

- local search (ls)
- simulated annealing (sa)
- variable neighborhood search (vns)
- tabu search (ts)
- genetic algorithm (ga)
- ant colony optimization (aco)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development purposes.

### Prerequisites

Make sure that g++ or mingw-w64 is installed.

### Installing

First you have to clone the git project:

```
git clone https://github.com/msommacal/tsp.git
```

Then you can compile the project using Make:

```
make
```

You can compile for Windows with the following target:

```
make win
```

### Usage

To execute the software, you only need to use the following command:

```
bin/tsp data/data.txt
```

You can also execute only some algorithms with special commands:

```
bin/tsp --bf --vns --ts data/data.txt
```

### Benchmark

![Benchmark](img/benchmark.png?raw=true "Benchmark")

## License

This project is licensed under the GNU General Public License - see the [LICENSE.md](LICENSE.md) file for details.
