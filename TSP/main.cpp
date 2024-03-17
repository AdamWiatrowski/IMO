// 1. Zrobić jeden cykl - potem podzielić na 2, w miejscu, które powoduje namniejsze długości.
// 2. Najpierw podzielić wierzchołki - potem osobno poszukać cykli.
// 3. Dobieramy do obu cykli na bieżąco. (?)
// Inne pomysły...?

#include <iostream>
#include <string>

#include "tsp_file.h"
#include "tsp_greedy_nn.h"
#include "tsp_greedy_cycle.h"
#include "tsp_greedy_regret.h"

using namespace std;


int main()
{
    string file_name_1 = "kroA100.tsp";
    string file_name_2 = "kroB100.tsp";
    
    TSP tsp(file_name_1);

    //tsp.printDistance();

    //startGreedyNN(tsp);
    //startGreedyCycle(tsp);
    startGreedyRegret(tsp);
    
    return 0;
}

