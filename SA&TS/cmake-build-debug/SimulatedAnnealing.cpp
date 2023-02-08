//
// Created by Katarzyna Hajduk on 29.11.2022.
//

#include "SimulatedAnnealing.h"
#include <iostream>
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

SimulatedAnnealing::~SimulatedAnnealing() {
    for (int i = 0; i < size; i++)
        delete[] matrix[i];
    delete[] matrix;
    size = 0;
}

void SimulatedAnnealing::createMatrix(Matrix mat){
    //Wpisywanie matrycy do matrycy, na której będę operować
    size = mat.getSize();

    matrix = new int *[size];
    for (int i = 0; i < size; i++)
        matrix[i] = new int [size];

    for(int i = 0; i < mat.getSize(); i++){
        for(int j = 0; j < mat.getSize(); j++)
            matrix[i][j] = mat.getValue(i, j);
    }
}

long long int SimulatedAnnealing::read_QPC() { //Funkcja licząca czas
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

double SimulatedAnnealing::getProbability(int cost, int newCost, double temperature) { //Liczenie prawdopodobieństwa
//    double delta = double(newCost) - double(cost);
//
//    if(delta >= 0)
//        return exp((-(delta/temperature)));
//    else
//        return 1;

    return exp((double(cost)-double(newCost))/temperature);
}

//Definicja sąsiedztwa
vector<int> SimulatedAnnealing::changeNeighbors(vector<int> path) { //Zmiana dwóch losowych miast ze sobą w drodze
    int city1 = rand() % (size - 1);
    int city2 = rand() % (size - 1);

    while (city1 == city2) //Sprawdzamy, czy nie są równe
        city2 = rand() % (size - 1);

    swap((path)[city1], (path)[city2]);

    return path;
}


vector<int> SimulatedAnnealing::generateInitPath() {
    initX = rand() % (size - 1); //Losujemy początkowy wierzchołek

    bool* visited = new bool[size]; //Lista odwiedzonych wierzchołków
    for (int i = 0; i < size; i++)
        visited[i] = false;
    visited[initX] = true;

    vector<int> path;
    path.push_back(initX);
    int minNode = initX;

    //Szukamy po kolei najkrótszej ścieżki i wrzucamy do początkowej drogi
    for (int i = 0; i < size - 1; i++){
        int minCost = INT_MAX;
        for (int j = 0; j < size; j++){
            if (!visited[j] && matrix[path[path.size()-1]][j] < minCost){
                minCost = matrix[path[path.size() - 1]][j];
                minNode = j;
            }
        }
        path.push_back(minNode);
        visited[minNode] = true;
    }

    //Usuwamy initX z path
    path.erase(path.begin());
    delete[] visited;
    return path;
}

int SimulatedAnnealing::getPathCost(vector <int> path){ //Liczenie kosztu dla danej ścieżki
    int cost = 0;

    cost += matrix[initX][path[0]];
    for (int i = 0; i < path.size() - 1; i++)
        cost += matrix[path[i]][path[i + 1]];

    cost += matrix[path[path.size() - 1]][initX];

    return cost;
}

double SimulatedAnnealing::updateTemperature(double oldTemperature, double alpha){
    return oldTemperature * alpha;
}

double SimulatedAnnealing::updateTemperature2(double oldTemperature, double alpha, int era){
    return ((pow(alpha, (double)era)) * oldTemperature);
}

double SimulatedAnnealing::updateTemperature3(double oldTemperature, double alpha, int era, double beta){
    return (oldTemperature / (alpha + beta * (double)era));
}

void SimulatedAnnealing::simulateAnnealing(int timeToStop, double alpha, int cooling, double beta) {
    QueryPerformanceFrequency((LARGE_INTEGER*)&frequency); //Ustawienie czasu
    startTime = read_QPC();

    srand(time(NULL));

    vector<int> path = generateInitPath(); //Znajdujemy początkową drogę
    int cost = getPathCost(path); //I początkowy koszt

    double temperature = setInitTemperature(cost, alpha); //Temperatura początkowa
    long long int endTime = 0; //Warunek stopu

    int eraLength = size; //Ilość epok
    int eraNumber = 1; //Inne liczenie schłodzenia

    while (endTime < timeToStop) { //Sprawdzamy warunek stopu
        vector<int> localBest = path;
        int localBestCost = cost;
        vector<int> newPath;

        for (int i = 0; i < eraLength; i++) { //Epoki
            newPath = localBest;
            newPath = changeNeighbors(newPath);
            int newCost = getPathCost(newPath);

            if (newCost < localBestCost) {
                localBest = newPath;
                localBestCost = newCost;
                eraNumber = i;
            }

            else  { //Przyjmujemy ścieżkę gorszą, jeżeli prawdopodobieństwo jest mniejsze od liczby wylosowanej z zakresu [0;1]
                double probability = getProbability(localBestCost, newCost, temperature);
                double randomNumber = (double)(rand() % 999) / 1000.0;

                if (randomNumber < probability) {
                    localBest = newPath;
                    localBestCost = newCost;
                }
            }
        }
        if (localBestCost < cost) {
            path = localBest;
            cost = localBestCost;
        }

        //Po epokach aktualizujemy temperature i czas
        if (cooling == 1)
            temperature = updateTemperature(temperature, alpha);
        else if (cooling == 2)
            temperature = updateTemperature2(temperature, alpha, eraNumber);
        else
            temperature = updateTemperature3(temperature, alpha, eraNumber, beta);

        endTime = ((read_QPC() - startTime) / frequency);
    }

    //Osobno wyświetlanie
    displayPath(path); //Wyświetlanie wyniku
    displayResult(cost, endTime, temperature);
}

double SimulatedAnnealing::calculateRelativeError(int result, int optimalSolution){ //Liczenie błędu względnego
    return ((abs((double)result - (double)optimalSolution) / (double)optimalSolution) * 100);
}

void SimulatedAnnealing::displayResult(int cost, int time, double temperature){
    cout << "Koszt: " << cost << endl;
//    cout << "Czas: " << setprecision(3) << (1000.0 * time) << "[ms]" << endl;

//    cout << "Koncowa temperatura: " << temperature << "[T]" << endl;

//    double error;
//    if(size == 48) {
//        error = calculateRelativeError(1776, cost);
//        cout << "Blad wzgledny: " << error << "[%]" << endl;
//    }
//    else if(size == 171) {
//        error = calculateRelativeError(2755, cost);
//        cout << "Blad wzgledny: " << error << "[%]" << endl;
//    }
//    else if(size == 403) {
//        error = calculateRelativeError(2465, cost);
//        cout << "Blad wzgledny: " << error << "[%]" << endl;
//    }
}

void SimulatedAnnealing::displayPath(std::vector<int> path) { //Wyświetlanie końcowego wyniku
    cout << "\n\nRozwiazanie: " << endl;
    cout << initX << " -> ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " -> ";
    }
    cout << initX << endl;
}

double SimulatedAnnealing::setInitTemperature(int cost, double alpha){
    return cost * alpha; //Temperatura początkowa
}
