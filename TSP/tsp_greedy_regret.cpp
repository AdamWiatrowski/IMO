#include "tsp_greedy_regret.h"

vector<bool> visited_RG(SIZE, false);

vector<int> cycle_1_RG;
vector<int> cycle_2_RG;

int totalCount_RG = 0;


void find_nearest_neighbor_RG(vector<int>& cycle, TSP tsp) {

	if (totalCount_RG == SIZE) {
		return;
	}

	int current = cycle.back();

	int min = numeric_limits<int>::max();
	int index = 0;

	for (int i = 0; i < SIZE; i++) {
		if (!visited_RG[i]) {
			if (tsp.distanceMatrix[current][i] < min) {
				min = tsp.distanceMatrix[current][i];
				index = i;
			}
		}
	}

	visited_RG[index] = true;
	cycle.push_back(index);
	totalCount_RG++;
}

void find_best_regret(vector<int>& cycle, TSP tsp) {
	
	if (totalCount_RG == SIZE) {
		return;
	}

	if (cycle.size() == 2) {
		int l = cycle[0];
		int r = cycle[1];

		int min = numeric_limits<int>::max();
		int index = 0;

		for (int i = 0; i < SIZE; i++) {
			int d1 = tsp.distanceMatrix[l][i];
			int d2 = tsp.distanceMatrix[r][i];
			int d3 = tsp.distanceMatrix[r][l];

			int d = d1 + d2 - d3;
			
			if (d < min) {
				min = d;
				index = i;
			}
		}

		visited_RG[index] = true;
		cycle.push_back(index);
		totalCount_RG++;
		return;
	}

	vector<vector<int>> cities;

	for (int i = 0; i < SIZE; i++) {
		if (!visited_RG[i]) {
			
			vector<int> scores;

			for (int j = 0; j < cycle.size(); j++) {
			
				int l = cycle[j];
				int r = cycle[(j + 1) % cycle.size()];

				int d1 = tsp.distanceMatrix[i][l];
				int d2 = tsp.distanceMatrix[i][r];
				int d3 = tsp.distanceMatrix[r][l];

				int score = d1 + d2 - d3;

				scores.push_back(score);
			}

			cities.push_back(scores);
		
		}
	}

	vector<int> regret;

	for (int i = 0; i < cities.size(); i++) {
		sort(cities[i].begin(), cities[i].end());
		int delta = cities[i][1] - cities[i][0];
		regret.push_back(delta);
	}

	int max = 0;
	int index = 0;

	for (int i = 0; i < regret.size(); i++) {
		if (regret[i] > max) {
			max = regret[i];
			index = i;
		}
	}

	int true_index = 0;
	int x = 0;

	for (int i = 0; i < SIZE; i++) {
		if (!visited_RG[i]) {
			if (x == index) {
				true_index = i;
			}
			x++;
		}
	}

	int spot = 0;
	int min = numeric_limits<int>::max();

	for (int j = 0; j < cycle.size(); j++) {

		int l = cycle[j];
		int r = cycle[(j + 1) % cycle.size()];

		int d1 = tsp.distanceMatrix[true_index][l];
		int d2 = tsp.distanceMatrix[true_index][r];
		int d3 = tsp.distanceMatrix[l][r];

		if (d1 + d2 - d3 < min) {
			min = d1 + d2 - d3;
			spot = j;
		}
	}

	visited_RG[true_index] = true;
	cycle.insert(cycle.begin() + spot + 1, true_index);
	totalCount_RG++;

}


void startGreedyRegret(TSP tsp) {

	cout << "== Greedy Regret ==" << endl;
	cout << "Rozpoczynam szukanie cyklu dla: " << tsp.fileName << endl;

	int totalDistance_1 = 0;
	int totalDistance_2 = 0;

	srand((unsigned)time(NULL));

	int current = rand() % 100;
	visited_RG[current] = true;
	cycle_1_RG.push_back(current);
	totalCount_RG++;

	cout << "Wylosowany: " << current + 1 << endl;

	int max = 0;
	int index = 0;

	for (int i = 0; i < SIZE; i++) {
		if (!visited_RG[i]) {
			if (tsp.distanceMatrix[current][i] > max) {
				max = tsp.distanceMatrix[current][i];
				index = i;
			}
		}
	}

	visited_RG[index] = true;
	cycle_2_RG.push_back(index);
	totalCount_RG++;

	cout << "Najdalszy: " << index + 1 << endl << endl;

	find_nearest_neighbor_RG(cycle_1_RG, tsp);
	find_nearest_neighbor_RG(cycle_2_RG, tsp);

	while (totalCount_RG != SIZE) {
		find_best_regret(cycle_1_RG, tsp);
		find_best_regret(cycle_2_RG, tsp);
	}


	cout << "Cykl 1. :" << endl;
	cout << "[";
	for (int x = 0; x < cycle_1_RG.size(); x++) {
		cout << cycle_1_RG[x] + 1 << ",";
		totalDistance_1 += tsp.distanceMatrix[cycle_1_RG[x]][cycle_1_RG[(x + 1) % cycle_1_RG.size()]];
	}
	cout << cycle_1_RG[0] + 1;
	cout << "]" << endl;

	cout << "Dlugosc: " << totalDistance_1 << endl << endl;

	cout << "Cykl 2. :" << endl;
	cout << "[";
	for (int x = 0; x < cycle_2_RG.size(); x++) {
		cout << cycle_2_RG[x] + 1 << ",";
		totalDistance_2 += tsp.distanceMatrix[cycle_2_RG[x]][cycle_2_RG[(x + 1) % cycle_2_RG.size()]];
	}
	cout << cycle_2_RG[0] + 1;
	cout << "]" << endl;

	cout << "Dlugosc: " << totalDistance_2 << endl << endl;

	cout << "SUMA: " << totalDistance_1 + totalDistance_2 << endl << endl;

}