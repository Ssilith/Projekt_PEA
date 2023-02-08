//
// Created by Katarzyna Hajduk on 21.12.2022.
//

#include <iostream>
#include "Test.h"

using namespace std;

void Test::geneticAlgorithm() {
    int choice;
    int timeToStop = 10;
    float crossover = 0.8;
    float mutation = 0.01;
    int population = 100;
    int mutationType = 1;

    do {
        cout << "\n\n# GENETIC ALGORITHM #" << endl;
        cout << "[1]. Wczytaj macierz z pliku" << endl;
        cout << "[2]. Wyswietl macierz" << endl;
        cout << "[3]. Wprowadz kryterium stopu" << endl;
        cout << "[4]. Wprowadz wielkosc populacji poczatkowej" << endl;
        cout << "[5]. Wprowadz wspolczynnik mutacji" << endl;
        cout << "[6]. Wprowadz wspolczynnik krzyzowania" << endl;
        cout << "[7]. Wybierz metode mutacji" << endl;
        cout << "[8]. Wykonaj algorytm Genetic Algorithm" << endl;
        cout << "[0]. Wyjscie" << endl;
        cout << "Podaj swoj wybor: ";
        cin >> choice;

        while (choice > 8 || choice < 0) {
            cout << "Podales zla liczbe. Wybierz ponownie: ";
            cin >> choice;
        }

        switch (choice) {
            case 0:
                return;

            case 1:
                matrix.loadMatrix();
                break;

            case 2:
                matrix.displayMatrix();
                break;

            case 3:
                cout << "Podaj czas w sekundach: ";
                cin >> timeToStop;
                break;

            case 4:
                cout << "Podaj wielkosc populacji poczatkowej: ";
                cin >> population;
                break;

            case 5:
                cout << "Podaj wspolczynnik mutacji: ";
                cin >> mutation;
                break;

            case 6:
                cout << "Podaj wspolczynnik krzyzowania: ";
                cin >> crossover;
                break;

            case 7:
                cout << "Wybierz metode mutacji: " << endl;
                cout << "[1]. Swap" << endl;
                cout << "[2]. Inverse" << endl;
                cout << "Wybor: ";
                cin >> mutationType;
                break;

            case 8:
                geneticalgorithm.createMatrix(matrix);
                geneticalgorithm.displayResult(timeToStop, population, mutation, crossover, mutationType);
                break;
        }
    } while (choice != 0);
}
