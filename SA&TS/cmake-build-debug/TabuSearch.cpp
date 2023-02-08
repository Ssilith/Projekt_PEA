//
// Created by Katarzyna Hajduk on 29.11.2022.
//

#include <windows.h>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "TabuSearch.h"

using namespace std;

TabuSearch::~TabuSearch() {
    for (int i = 0; i < size; i++)
        delete[] matrix[i];
    delete[] matrix;
    size = 0;
}

void TabuSearch::createMatrix(Matrix mat){
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

long long int TabuSearch::read_QPC() { //Funkcja licząca czas
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return((long long int)count.QuadPart);
}

double TabuSearch::calculateRelativeError(int result, int optimalSolution){ //Liczenie błędu względnego
    return ((abs((double)optimalSolution - (double)result) / (double)optimalSolution) * 100);
}

int TabuSearch::getPathCost(vector <int> path){ //Liczenie kosztu dla danej ścieżki
    int cost = 0;

    cost += matrix[initX][path[0]];
    for (int i = 0; i < path.size() - 1; i++)
        cost += matrix[path[i]][path[i + 1]];
    cost += matrix[path[path.size() - 1]][initX];

    return cost;
}

//Definicja sąsiedztwa
vector<int> TabuSearch::changeNeighbors(vector<int> path, int cost, int aspiration) { //Zmiana dwóch losowych miast ze sobą w drodze
    vector<int> localPath = path;
    int city1, city2;
    bool inTabu = false;

    for (int i = 0; i < size; i++) {
        do {
            city1 = rand() % (size - 1);
            city2 = rand() % (size - 1);

            while (city1 == city2) //Sprawdzamy, czy nie są równe
                city2 = rand() % (size - 1);

            if (tabuList.size() != 0) {
                inTabu = isInTabu(tabuList, city1, city2);

                if (inTabu) { //Kryterium aspiracji, jeżeli jest w TabuList, ale wynik jest lepszy to pozwalamy na złamanie zakazu
                    aspiration++;
                    vector<int> tempPath = path;
                    swap((tempPath)[city1], (tempPath)[city2]);
                    int tempCost = getPathCost(tempPath);

                    if (tempCost < cost && aspiration > 10) { //Aspiracja
                        inTabu = false;
                    }
                }
            }
        } while (inTabu); //Sprawdzamy, czy nie ma w tabu list

        swap((path)[city1], (path)[city2]);

        if (getPathCost(path) < cost) {
            localPath = path;
            move1 = city1;
            move2 = city2;
        }
    }
    return localPath;
}

vector<int> TabuSearch::changeNeighbors2(vector<int> path, int cost, int aspiration) { //Przeniesienie j-tego elementu na pozycję i-tą,
    vector<int> localPath = path;
    int takePosition, insertPosition;
    bool inTabu = false;

    for (int i = 0; i < size; i++) {
        do {
        takePosition = rand() % (size - 1); //Pozycja, z której zabieramy
        insertPosition = rand() % (size - 1); //Pozycja gdzie wstawiamy

        while (insertPosition == takePosition) //Sprawdzamy, czy nie są równe
            insertPosition = rand() % (size - 1);

        if(tabuList.size() != 0) {
            inTabu = isInTabu(tabuList, takePosition, insertPosition);

            if(inTabu){ //Kryterium aspiracji, jeżeli jest w TabuList, ale wynik jest lepszy to pozwalamy na złamanie zakazu
                vector <int> tempPath = path;

                tempPath.insert(tempPath.begin() + insertPosition, tempPath.at(takePosition));
                if(insertPosition > takePosition)
                    tempPath.erase(tempPath.begin() + takePosition);
                else
                    tempPath.erase(tempPath.begin() + takePosition - 1);

                int tempCost = getPathCost(tempPath);

                if (tempCost < cost && aspiration > 10) { //Aspiracja
                    inTabu = false;
                }
            }
        }
    } while (inTabu); //Sprawdzamy, czy nie ma w tabu list

        path.insert(path.begin() + insertPosition, path.at(takePosition));
        if(insertPosition > takePosition) //Usuwamy element z pozycji, z której zabraliśmy
            path.erase(path.begin() + takePosition);
        else
            path.erase(path.begin() + takePosition - 1);

        if (getPathCost(path) < cost) {
            localPath = path;
            move1 = takePosition;
            move2 = insertPosition;
        }
    }
    return localPath;
}

vector<int> TabuSearch::changeNeighbors3(vector<int> path, int cost, int aspiration) { //Odwrócenie kolejności w podciągu zaczynającym się na i-tej pozycji i kończącym się na pozycji j-tej.
    vector<int> localPath = path;
    int takePosition, insertPosition;
    bool inTabu = false;

    for (int i = 0; i < size; i++) {
        do {
            takePosition = rand() % (size - 1); //Pozycja 1 podciągu
            insertPosition = rand() % (size - 1); //Pozycja 2 podciągu

            while (insertPosition == takePosition) //Sprawdzamy, czy nie są równe
                insertPosition = rand() % (size - 1);

            if(tabuList.size() != 0) {
                inTabu = isInTabu(tabuList, takePosition, insertPosition);

                if(inTabu){ //Kryterium aspiracji, jeżeli jest w TabuList, ale wynik jest lepszy to pozwalamy na złamanie zakazu
                    vector <int> tempPath = path;

                    if(takePosition < insertPosition)
                        reverse(tempPath.begin() + takePosition, tempPath.begin() + insertPosition + 1);
                    else
                        reverse(tempPath.begin() + insertPosition, tempPath.begin() + takePosition + 1);

                    int tempCost = getPathCost(tempPath);

                    if (tempCost < cost && aspiration > 10) { //Aspiracja
                        inTabu = false;
                    }
                }
            }
        } while (inTabu); //Sprawdzamy, czy nie ma w tabu list

    if(takePosition < insertPosition)
        reverse(path.begin() + takePosition, path.begin() + insertPosition + 1);
    else
        reverse(path.begin() + insertPosition, path.begin() + takePosition + 1);

        if (getPathCost(path) < cost) {
            localPath = path;
            move1 = takePosition;
            move2 = insertPosition;
        }
    }

    return localPath;
}

bool TabuSearch::isInTabu(vector<int> tabuList, int city1, int city2){ //Sprawdzenie, czy takie przejście jest w TabuList
    bool inTabu = false;
    for(int i = 0; i < tabuList.size() - 1; i++){
        if(tabuList.at(i) == city1){
            if(tabuList.at(i + 1) == city2)
                inTabu = true;
        }
    }
    return inTabu;
}

vector<int> TabuSearch::generateInitPath() {
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

void TabuSearch::displayPath(std::vector<int> path) { //Wyświetlanie końcowego wyniku
    cout << "\n\nRozwiazanie: " << endl;
    cout << initX << " -> ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " -> ";
    }
    cout << initX << endl;
}

void TabuSearch::tabuSearch(int timeToStop, int neighbor) {
    QueryPerformanceFrequency((LARGE_INTEGER *) &frequency); //Ustawienie czasu
    startTime = read_QPC();

    srand(time(NULL));

    vector<int> path = generateInitPath(); //Znajdujemy początkową drogę
    int cost = getPathCost(path); //I początkowy koszt

    vector<int> bestPath;
    int bestPathCost;
    int iterCounter = 0;

    long long int endTime = 0; //Warunek stopu
    int aspiration = 0;

    while (endTime < timeToStop) { //Sprawdzamy warunek stopu
        bestPath = path;
        bestPathCost = cost;
        vector<int> newPath;

//        for(int i = 0; i < size; i++) {
            if (neighbor == 1)
                newPath = changeNeighbors(bestPath, cost, aspiration); //Zamieniamy 2 węzły
            else if (neighbor == 2)
                newPath = changeNeighbors2(bestPath, cost, aspiration); //Insert
            else
                newPath = changeNeighbors3(bestPath, cost, aspiration); //Invert

            iterCounter++; //Zwiększamy licznik iteracji
            int newCost = getPathCost(newPath);

            //Jeżeli zmiana poprawia ścieżkę to nadpisujemy
            if (newCost < bestPathCost) {
                bestPath = newPath;
                bestPathCost = newCost;
                iterCounter = 0;

                tabuList.push_back(move1);
                tabuList.push_back(move2);
            }

            //Usuwanie przejścia z listy tabu po danej ilości iteracji
            if (tabuList.size() == size / 2) { //Długość kadencji
                tabuList.erase(tabuList.begin());
                tabuList.erase(tabuList.begin());
            }

            //Dywersyfikacja, jeżeli długo nie nastąpiła zmiana to losujemy od nowa
            if (iterCounter == size) {
                path = generateRandomPath();
                iterCounter = 0;

                tabuList.clear();
            }
//        }
        endTime = ((read_QPC() - startTime) / frequency);
    }

    tabuList.clear(); //Wyczyszczenie tabuList
    displayPath(bestPath); //Wyświetlanie wyniku
    displayResult(bestPathCost, endTime);
}

vector<int> TabuSearch::generateRandomPath() {
    //Tworzenie nowej ścieżki bez initX, które się nie zmienia
    vector<int> path;

    for (int i = 0; i < size; i++) {
        if(i != initX)
            path.push_back(i);
    }

    random_shuffle(path.begin(), path.end());

    return path;
}

void TabuSearch::displayResult(int cost, int time){
    cout << "Koszt: " << cost << endl;
//    cout << "Czas: " << setprecision(3) << (1000.0 * time) << "[ms]" << endl;

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