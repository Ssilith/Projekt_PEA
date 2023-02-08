//
// Created by Katarzyna Hajduk on 20.10.2022.
//

#include <iostream>
#include <algorithm>
#include "BruteForce.h"

using namespace std;

BruteForce::BruteForce(){}

BruteForce::~BruteForce(){
    delete[] path;
    delete[] array;
}

void BruteForce::TSP(Matrix matrix){
    minDistance = INT_MAX; //Ustawiamy wartość minDistance na maksymalna
    path = new int[matrix.getSize()]; //Zmienna, w której będzie przechowywany końcowa, najkrótsza droga
    array = new int[matrix.getSize()]; //Dodatkowa zmienna używana do wyznaczenia permutacji

    for (int i = 0; i < matrix.getSize(); i++) //Wypełnienie array od 0 do N-1, gdzie N to liczba miast
        array[i] = i;

    do {
        distance = 0;
        for (int i = 0; i < matrix.getSize() - 1; i++) {
            int firstCity = array[i]; //Wyznaczenie kolejnych miast według permutacji
            int secondCity = array[i + 1];
            distance += matrix.getValue(firstCity, secondCity); //Dodanie wartości do drogi
        }
        distance += matrix.getValue(array[matrix.getSize() - 1], array[0]);

        if (distance < minDistance) { //Sprawdzenie i nadpisanie krótszej drogi
            minDistance = distance;
            for (int i = 0; i < matrix.getSize(); i++)
                path[i] = array[i];
        }

        for(int k = 0; k < matrix.getSize(); k++)
            cout << array[k] << ' ';
        cout << endl;

    } while (next_permutation(array, array + matrix.getSize() - 1)); //Wyznaczanie kolejnych permutacji
}

void BruteForce::displayResult(Matrix matrix){
    cout << "Minimum distance: " << minDistance << endl; //Wypisanie wyniku
    for(int i = 0; i < matrix.getSize(); i++)
        cout << path[i] << " -> ";
    cout << path[0];
}
