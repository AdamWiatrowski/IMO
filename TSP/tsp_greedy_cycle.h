#ifndef GREEDY_C
#define GREEDY_C

#include <limits>
#include <vector>
#include <cmath>


#include "tsp_file.h"

using namespace std;

void startGreedyCycle(TSP tsp);
void find_nearest_neighbor(vector<int>& cycle, TSP tsp);
void find_best_split(vector<int>& cycle, TSP tsp);

#endif
