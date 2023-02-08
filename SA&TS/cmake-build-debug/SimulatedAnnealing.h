//
// Created by Katarzyna Hajduk on 29.11.2022.
//

#ifndef PEA_SIMULATEDANNEALING_H
#define PEA_SIMULATEDANNEALING_H
#include "Matrix.h"
#include <vector>

using namespace std;

class SimulatedAnnealing {
private:
    int size;
    int **matrix;
    int initX;
    long long int startTime;
    long long int frequency;

public:
    ~SimulatedAnnealing();
    long long int read_QPC();
    void createMatrix(Matrix mat);
    void simulateAnnealing(int timeToStop, double alpha, int cooling, double beta);
    vector<int> generateInitPath();
    int getPathCost(vector<int> path);
    vector<int> changeNeighbors(vector<int> path);
    double getProbability(int cost, int newCost, double temperature);
    double updateTemperature(double oldTemperature, double alpha);
    void displayPath(vector<int> path);
    double calculateRelativeError(int result, int optimalSolution);
    void displayResult(int cost, int timeSpent, double temperature);
    double updateTemperature2(double oldTemperature, double alpha, int era);
    double updateTemperature3(double oldTemperature, double alpha, int era, double beta);
    double setInitTemperature(int cost, double alpha);
};


#endif //PEA_SIMULATEDANNEALING_H
