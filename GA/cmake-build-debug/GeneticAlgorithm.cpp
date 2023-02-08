//
// Created by Katarzyna Hajduk on 21.12.2022.
//

#include "GeneticAlgorithm.h"
#include <windows.h>
#include <algorithm>
#include <iostream>

using namespace std;

GeneticAlgorithm::~GeneticAlgorithm() {
    for (int i = 0; i < size; i++)
        delete[] matrix[i];
    delete[] matrix;
    size = 0;
}

void GeneticAlgorithm::createMatrix(Matrix mat) {
    //Wpisywanie matrycy do macierzy, na której będę operować
    size = mat.getSize();

    matrix = new int *[size];
    for (int i = 0; i < size; i++)
        matrix[i] = new int[size];

    for (int i = 0; i < mat.getSize(); i++) {
        for (int j = 0; j < mat.getSize(); j++)
            matrix[i][j] = mat.getValue(i, j);
    }
}

long long int GeneticAlgorithm::read_QPC() { //Funkcja licząca czas
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int) count.QuadPart);
}

double GeneticAlgorithm::calculateRelativeError(int result, int optimalSolution) { //Liczenie błędu względnego
    return ((abs((double) result - (double) optimalSolution) / (double) optimalSolution) * 100);
}

void GeneticAlgorithm::geneticAlgorithm(int timeToStop, int population, float mutation, float crossover, int mutationType) {
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency); //Ustawienie czasu
    startTime = read_QPC();

    srand(time(NULL));

    long long int endTime = 0; //Warunek stopu

    vector<vector<int>> firstPopulation; //Tworzenie pierwszej populacji
    generateFirstPopulation(firstPopulation, population);

    pair<vector<int>, vector<int>> children;
    vector<vector<int>> parents;
    vector<int> child;
    fitness.resize(population);

    while (endTime < timeToStop) { //Sprawdzamy warunek stopu
        fitnessCost(firstPopulation);
        parents = tournament(firstPopulation);

        children = crossoverProbability(parents[0], parents[1], crossover);
        firstPopulation.push_back(children.first);
        firstPopulation.push_back(children.second);

        for(int i = 0; i < population; i++){
            child = mutationProbability(firstPopulation[i], mutation, mutationType);
            firstPopulation.push_back(child);
        }

        sortPopulation(firstPopulation, population);
        endTime = ((read_QPC() - startTime) / frequency);
    }
    fitnessCost(firstPopulation);
}

int GeneticAlgorithm::getPathCost(vector<int> path) { //Liczenie kosztu dla danej ścieżki
    int cost = 0;
    for (int i = 0; i < path.size() - 1; i++)
        cost += matrix[path[i]][path[i + 1]];
    cost += matrix[path[path.size() - 1]][path[0]];

    return cost;
}

void GeneticAlgorithm::generateFirstPopulation(vector<vector<int>> &firstPopulation, int populationSize) { //Tworzenie populacji początkowej
    vector<int> path;
    for (int i = 0; i < size; i++)
        path.push_back(i);

    for (int i = 0; i < populationSize; i++) {
        random_shuffle(path.begin(), path.end());
        firstPopulation.push_back(path);
    }
}

pair<vector<int>, vector<int>> GeneticAlgorithm::crossoverOX(vector<int> firstPath, vector<int> secondPath) { //Drugi rodzaj krzyżowania — krzyżowanie OX
    vector<int> firstChild;
    vector<int> secondChild;
    int x, y;

    firstChild.resize(size, -1);
    secondChild.resize(size, -1);

    vector<int> tmpFirstChild;
    vector<int> tmpSecondChild;

    bool *firstMapping = new bool[size];
    bool *secondMapping = new bool[size];

    for (int i = 0; i < size; i++) {
        firstMapping[i] = false;
        secondMapping[i] = false;
    }

    do { //Punkty krzyżowania
        x = rand() % (size - 1);
        y = rand() % (size - 1);
    } while (x == y || x > y);

    for (int i = x; i < y; i++) { //Wpisujemy wartość między punktami krzyżowania
        firstChild[i] = firstPath[i];
        secondChild[i] = secondPath[i];

        firstMapping[firstPath[i]] = true; //Zapisujemy wartości, które już wystąpiły
        secondMapping[secondPath[i]] = true;
    }

    for (int i = y; i < size; i++) { //Wpisywanie wartości wierzchołków po punkcie krzyżowania z wyłączeniem tych, które już wystąpiły
        if (!firstMapping[secondPath[i]])
            tmpFirstChild.push_back(secondPath[i]);

        if (!secondMapping[firstPath[i]])
            tmpSecondChild.push_back(firstPath[i]);
    }

    for (int i = 0; i < y; i++) {
        if (!firstMapping[secondPath[i]])
            tmpFirstChild.push_back(secondPath[i]);

        if (!secondMapping[firstPath[i]])
            tmpSecondChild.push_back(firstPath[i]);
    }

    int actFirstPosition = 0;
    int actSecondPosition = 0;
    for (int i = y; i < size; i++) {
        if (firstChild.at(i) == -1) {
            firstChild[i] = tmpFirstChild[actFirstPosition];
            actFirstPosition++;
        }
        if (secondChild.at(i) == -1) {
            secondChild[i] = tmpSecondChild[actSecondPosition];
            actSecondPosition++;
        }
    }

    for (int i = 0; i < x; i++) {
        if (firstChild.at(i) == -1) {
            firstChild[i] = tmpFirstChild[actFirstPosition];
            actFirstPosition++;
        }
        if (secondChild.at(i) == -1) {
            secondChild[i] = tmpSecondChild[actSecondPosition];
            actSecondPosition++;
        }
    }

    delete[] firstMapping;
    delete[] secondMapping;

    return make_pair(firstChild, secondChild);
}

vector<int> GeneticAlgorithm::mutationSwap(vector<int> path) { //Pierwszy rodzaj mutacji — mutacja poprzez zamianę dwóch miast
    int first = rand() % path.size();
    int second;

    do {
        second = rand() % path.size();
    } while (second == first);

//    iter_swap(path.begin() + first, path.begin() + second);
    swap((path)[first], (path)[second]);

    return path;
}

vector<int> GeneticAlgorithm::mutationInverse(vector<int> path) { //Drugi rodzaj mutacji — mutacja poprzez inwersje
    int first = rand() % path.size();
    int second;

    do {
        second = rand() % path.size();
    } while (second == first);

    if (first < second)
        reverse(path.begin() + first, path.begin() + second + 1);
    else
        reverse(path.begin() + second, path.begin() + first + 1);

    return path;
}

vector<int> GeneticAlgorithm::mutationProbability(vector<int> path, float mutation, int mutationType) { //Funkcja pomocnicza licząca prawdopodobieństwo, że dana mutacja wystąpi
    float random = (float) ((rand() % 1000) / 1000);

    if (random <= mutation) {
        if (mutationType == 1) {
            return mutationSwap(path);
        } else {
            return mutationInverse(path);
        }
    } else
        return path;
}

pair<vector<int>, vector<int>> GeneticAlgorithm::crossoverProbability(vector<int> firstPath, vector<int> secondPath, float crossover) { //Funkcja pomocnicza licząca prawdopodobieństwo, że dane krzyżowanie wystąpi
    float random = (float) ((rand() % 1000) / 1000);

    if (random <= crossover)
        return crossoverOX(firstPath, secondPath);
    else
        return make_pair(firstPath, secondPath);
}

void GeneticAlgorithm::fitnessCost(vector<vector<int>> population) {
    for (int i = 0; i < population.size(); i++) {
        fitness[i] = getPathCost(population[i]);

        if (fitness[i] < bestCost) {
            bestPath = population[i];
            bestCost = fitness[i];
        }
    }
}

vector<vector<int>> GeneticAlgorithm::tournament(vector<vector<int>> population) { //Wybieranie rodziców do krzyżowania i mutacji
    vector<vector<int>> parents;
    parents.resize(2); //Szukamy dwóch rodziców

    int tournamentSize = population.size() / 10;

    for (int i = 0; i < 2; i++) {
        bestCost = INT_MAX;
        for (int j = 0; j < tournamentSize; j++) {
            int index = rand() % (population.size() - 1);
            int cost = fitness[index];

            if (cost < bestCost) { //Szukamy po najlepszym koszcie
                bestCost = cost;
                bestPath = population[index];
            }
        }
        parents[i] = bestPath;
    }

    return parents;
}

void GeneticAlgorithm::sortPopulation(vector<vector<int>> &population, int populationSize) { //Sortowanie populacji i usuwanie końcowych elementów z najwyższym kosztem, dopóki wielkość populacji nie równa się początkowej
    sort(population.begin(), population.end(), [this](auto i, auto j) -> bool {
        return getPathCost(i) < getPathCost(j);
    });

    while (population.size() != populationSize) {
        population.pop_back();
    }
}

void GeneticAlgorithm::displayResult(int timeToStop, int population, float mutation, float crossover, int mutationType){
    geneticAlgorithm(timeToStop, population, mutation, crossover, mutationType);

    cout << "Wyniki:" << endl;

    cout << "Najlepsza droga: ";
    for (int i = 0; i < bestPath.size(); i++) {
        cout << bestPath[i] << " -> ";
    }
    cout << bestPath[0] << endl;

    int cost = getPathCost(bestPath);
    cout << "Najlepszy koszt: " << cost << endl;

//    double error;
//    if(size == 48) {
//        error = calculateRelativeError(cost, 1776);
//        cout << "Blad wzgledny: " << error << "[%]" << endl;
//    }
//    else if(size == 171) {
//        error = calculateRelativeError(cost, 2755);
//        cout << "Blad wzgledny: " << error << "[%]" << endl;
//    }
//    else if(size == 403) {
//        error = calculateRelativeError(cost, 2465);
//        cout << "Blad wzgledny: " << error << "[%]" << endl;
//    }
}