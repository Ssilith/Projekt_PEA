//
// Created by Katarzyna Hajduk on 29.11.2022.
//

#ifndef PEA_TABUSEARCH_H
#define PEA_TABUSEARCH_H
#include "Matrix.h"
#include <vector>

using namespace std;

class TabuSearch {
private:
    int size;
    int **matrix;
    int initX;
    long long int startTime;
    long long int frequency;
    int move1, move2;
    vector<int> tabuList;

public:
    ~TabuSearch();
    double calculateRelativeError(int result, int optimalSolution);
    void createMatrix(Matrix mat);
    long long int read_QPC();
    vector<int> generateInitPath();
    int getPathCost(vector<int> path);
    void displayPath(vector<int> path);
    void tabuSearch(int timeToStop, int neighbor);
    vector<int> generateRandomPath();
    bool isInTabu(vector<int> tabuList, int city1, int city2);
    void displayResult(int cost, int time);
    vector<int> changeNeighbors(vector<int> path, int cost, int aspiration);
    vector<int> changeNeighbors2(vector<int> path, int cost, int aspiration);
    vector<int> changeNeighbors3(vector<int> path, int cost, int aspiration);
};


#endif //PEA_TABUSEARCH_H
