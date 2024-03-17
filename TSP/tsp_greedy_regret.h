#ifndef GREEDY_REGRET
#define GREEDY_REGRET

#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <utility>
#include <algorithm>

#include "tsp_file.h"

using namespace std;

void startGreedyRegret(TSP tsp);
void find_nearest_neighbor_RG(vector<int>& cycle, TSP tsp);
#endif