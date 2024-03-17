#include "tsp_file.h"

TSP::TSP(string name) : fileName(name) {
	cout << "Utworzono obiekt dla pliku: " << name << endl;

    loadFile();
    countDistanceMatrix();

    cout << endl;
}

int TSP::getDistance(int x1, int y1, int x2, int y2) {

    int dx = x1 - x2;
    int dy = y1 - y2;

    return sqrt(pow(dx, 2) + pow(dy, 2));
}


void TSP::loadFile() {
    ifstream file(fileName);
    string line;
    int count = 0;

    while (getline(file, line)) {
        count++;

        if (line == "EOF") {
            break;
        }

        if (count > 6) {
            istringstream ss(line);
            string firstElement;
            string secondElement;
            string thirdElement;

            while (getline(ss, firstElement, ' ')) {

                if (getline(ss, secondElement, ' ') && getline(ss, thirdElement, ' ')) {

                    vertices[stoi(firstElement) - 1][0] = stoi(secondElement);
                    vertices[stoi(firstElement) - 1][1] = stoi(thirdElement);
                }
            }
        }
    }

    file.close();

    cout << "Wczytano plik: " << fileName << endl;

    return;
}

void TSP::countDistanceMatrix() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            int x = getDistance(vertices[i][0], vertices[i][1], vertices[j][0], vertices[j][1]);

            distanceMatrix[i][j] = x;
            distanceMatrix[j][i] = x;
        }
    }

    cout << "Utworzono macierz odleglosci." << endl;
}

void TSP::printDistance() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << distanceMatrix[i][j] << " ";
        }
        cout << endl;
    }
}