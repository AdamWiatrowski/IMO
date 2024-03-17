#ifndef LOAD_H
#define LOAD_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;

#define SIZE 100

class TSP {
public:
    TSP(string fileName);
    string fileName;
    int distanceMatrix[SIZE][SIZE] = { 0 };
    void printDistance();

private:
    int vertices[SIZE][2] = { 0 };
    int getDistance(int x1, int y1, int x2, int y2);
    void countDistanceMatrix();
    void loadFile();
};

#endif