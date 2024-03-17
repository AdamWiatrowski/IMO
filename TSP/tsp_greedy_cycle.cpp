#include "tsp_greedy_cycle.h"

vector<bool> visited_GC(SIZE, false);

vector<int> cycle_1_GC;
vector<int> cycle_2_GC;

int totalCount_GC = 0;

void find_nearest_neighbor(vector<int>& cycle, TSP tsp) {

	if (totalCount_GC == SIZE) {
		return;
	}

	int current = cycle.back();

	int min = numeric_limits<int>::max();
	int index = 0;

	for (int i = 0; i < SIZE; i++) {
		if (!visited_GC[i]) {
			if (tsp.distanceMatrix[current][i] < min) {
				min = tsp.distanceMatrix[current][i];
				index = i;
			}
		}
	}

	visited_GC[index] = true;
	cycle.push_back(index);
	totalCount_GC++;
}

void find_best_split(vector<int>& cycle, TSP tsp) {
	
	if (totalCount_GC == SIZE) {
		return;
	}


	int min_add = numeric_limits<int>::max();
	int index_add = 0;
	int spot = 0;

	for (int i = 0; i < cycle.size() - 1; i++) {

		int l = cycle[i];
		int r = cycle[(i + 1) % cycle.size()];

		int min = numeric_limits<int>::max();
		int index = 0;

		for (int j = 0; j < SIZE; j++) {
			if (!visited_GC[j]) {
				int d1 = tsp.distanceMatrix[l][j];
				int d2 = tsp.distanceMatrix[r][j];
				int d3 = tsp.distanceMatrix[l][r];
				int d = d1 + d2 - d3;

				if (d < min) {
					min = d;
					index = j;
				}
			}
		}

		if (min < min_add) {
			min_add = min;
			index_add = index;
			spot = i;
		}

	}

	visited_GC[index_add] = true;
	cycle.insert(cycle.begin() + spot + 1, index_add);
	totalCount_GC++;
}

void startGreedyCycle(TSP tsp) {

	cout << "== Greedy Cycle ==" << endl;
	cout << "Rozpoczynam szukanie cyklu dla: " << tsp.fileName << endl;

	int totalDistance_1 = 0;
	int totalDistance_2 = 0;

	srand((unsigned)time(NULL));

	// time start

	int current = rand() % 100;
	visited_GC[current] = true;
	cycle_1_GC.push_back(current);
	totalCount_GC++;

	cout << "Wylosowany: " << current << endl;
	
	int max = 0;
	int index = 0;

	for (int i = 0; i < SIZE; i++) {
		if (!visited_GC[i]) {
			if (tsp.distanceMatrix[current][i] > max) {
				max = tsp.distanceMatrix[current][i];
				index = i;
			}
		}
	}

	visited_GC[index] = true;
	cycle_2_GC.push_back(index);
	totalCount_GC++;

	cout << "Najdalszy: " << index + 1 << endl << endl;


	find_nearest_neighbor(cycle_1_GC, tsp);
	find_nearest_neighbor(cycle_2_GC, tsp);


	while (totalCount_GC != SIZE) {
		find_best_split(cycle_1_GC, tsp);
		find_best_split(cycle_2_GC, tsp);
	}

	// time stop

	cout << "Cykl 1. :" << endl;
	cout << "[";
	for (int x = 0; x < cycle_1_GC.size(); x++) {
		cout << cycle_1_GC[x] + 1 << ",";
		totalDistance_1 += tsp.distanceMatrix[cycle_1_GC[x]][cycle_1_GC[(x + 1) % cycle_1_GC.size()]];
	}
	cout << cycle_1_GC[0] + 1;
	cout << "]" << endl;

	cout << "Dlugosc: " << totalDistance_1 << endl << endl;

	cout << "Cykl 2. :" << endl;
	cout << "[";
	for (int x = 0; x < cycle_2_GC.size(); x++) {
		cout << cycle_2_GC[x] + 1 << ",";
		totalDistance_2 += tsp.distanceMatrix[cycle_2_GC[x]][cycle_2_GC[(x + 1) % cycle_2_GC.size()]];
	}
	cout << cycle_2_GC[0] + 1;
	cout << "]" << endl;

	cout << "Dlugosc: " << totalDistance_2 << endl << endl;

	cout << "SUMA: " << totalDistance_1 + totalDistance_2 << endl << endl;

}
