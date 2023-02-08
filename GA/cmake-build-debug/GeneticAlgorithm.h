//
// Created by Katarzyna Hajduk on 21.12.2022.
//

#ifndef PEA_3_GENETICALGORITHM_H
#define PEA_3_GENETICALGORITHM_H

#include <vector>
#include "Matrix.h"

using namespace std;

class GeneticAlgorithm {
private:
    int size;
    int **matrix;
    long long int startTime;
    long long int frequency;
    vector<int> fitness;
    vector<int> bestPath;
    int bestCost;

public:
    ~GeneticAlgorithm();

    void createMatrix(Matrix mat);

    long long int read_QPC();

    double calculateRelativeError(int result, int optimalSolution);

    void geneticAlgorithm(int timeToStop, int population, float mutation, float crossover, int mutationType);

    int getPathCost(vector<int> path);

    void generateFirstPopulation(vector<vector<int>> &firstPopulation, int population);

    vector<int> mutationSwap(vector<int> path);

    vector<int> mutationInverse(vector<int> path);

    vector<int> mutationProbability(vector<int> path, float mutation, int mutationType);

    pair<vector<int>, vector<int>> crossoverProbability(vector<int> firstPath, vector<int> secondPath, float crossover);

    void fitnessCost(vector<vector<int>> population);

    pair<vector<int>, vector<int>> crossoverOX(vector<int> firstPath, vector<int> secondPath);

    vector<vector<int>> tournament(vector<vector<int>> population);

    void sortPopulation(vector<vector<int>> &population, int populationSize);

    void displayResult(int timeToStop, int population, float mutation, float crossover, int mutationType);
};


#endif //PEA_3_GENETICALGORITHM_H
