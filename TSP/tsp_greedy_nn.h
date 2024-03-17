#ifndef GREEDY_NN
#define GREEDY_NN

#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <cmath>

#include "tsp_file.h"

using namespace std;

void startGreedyNN(TSP tsp);
void add_nearest_neighbor(vector<int>& cycle, TSP tsp, int* totalDistance);
#endif
