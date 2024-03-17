#include "tsp_greedy_nn.h"



vector<bool> visited_NN(SIZE, false);

vector<int> cycle_1_NN;
vector<int> cycle_2_NN;

int totalCount_NN = 0;

void add_nearest_neighbor(vector<int>& cycle, TSP tsp, int* totalDistance) {

	if (totalCount_NN == SIZE) {
		return;
	}

	int current = cycle.back();

	int min = numeric_limits<int>::max();
	int index = 0;

	
	for (int i = 0; i < SIZE; i++) {
		if (!visited_NN[i]) {
			if (tsp.distanceMatrix[current][i] < min) {
				min = tsp.distanceMatrix[current][i];
				index = i;
			}
		}
	}

	visited_NN[index] = true;
	cycle.push_back(index);
	totalCount_NN++;
	*totalDistance += min;
}

void startGreedyNN(TSP tsp) {

	cout << "== Greedy Nearest Neighbor ==" << endl;
	cout << "Rozpoczynam szukanie cyklu dla: " << tsp.fileName << endl;

	int totalDistance_1 = 0;
	int totalDistance_2 = 0;

	srand((unsigned)time(NULL));

	// time start

	int current = rand() % 100;

	//current = 83;

	visited_NN[current] = true;
	cycle_1_NN.push_back(current);
	totalCount_NN++;

	cout << "Wylosowany: " << current + 1 << endl;

	int max = 0;
	int index = 0;

	for (int i = 0; i < SIZE; i++) {
		if (!visited_NN[i]) {
			if (tsp.distanceMatrix[current][i] > max) {
				max = tsp.distanceMatrix[current][i];
				index = i;
			}
		}
	}

	visited_NN[index] = true;
	cycle_2_NN.push_back(index);
	totalCount_NN++;

	cout << "Najdalszy: " << index + 1 << endl << endl;


	while (totalCount_NN != SIZE) {
		add_nearest_neighbor(cycle_1_NN, tsp, &totalDistance_1);
		add_nearest_neighbor(cycle_2_NN, tsp, &totalDistance_2);
	}

	totalDistance_1 += tsp.distanceMatrix[cycle_1_NN[0]][cycle_1_NN.back()];
	totalDistance_2 += tsp.distanceMatrix[cycle_2_NN[0]][cycle_2_NN.back()];

	// time stop

	cout << "Cykl 1. :" << endl;
	cout << "[";
	for (int x = 0; x < cycle_1_NN.size(); x++) {
		cout << cycle_1_NN[x] + 1 << ",";
	}
	cout << cycle_1_NN[0] + 1;
	cout << "]" << endl;

	cout << "Dlugosc: " << totalDistance_1 << endl << endl;

	cout << "Cykl 2. :" << endl;
	cout << "[";
	for (int x = 0; x < cycle_2_NN.size(); x++) {
		cout << cycle_2_NN[x] + 1 << ",";
	}
	cout << cycle_2_NN[0] + 1;
	cout << "]" << endl;

	cout << "Dlugosc: " << totalDistance_2 << endl << endl;

	cout << "SUMA: " << totalDistance_1 + totalDistance_2 << endl << endl;
	
}
