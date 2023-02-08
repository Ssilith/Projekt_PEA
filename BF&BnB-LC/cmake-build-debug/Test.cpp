//
// Created by Katarzyna Hajduk on 19.10.2022.
//

#include "Test.h"
#include <iostream>
#include <profileapi.h>
#include <iomanip>
#include "Matrix.h"
#include "BruteForce.h"
#include "BranchAndBound.h"

using namespace std;

void Test::bruteForce(){
    int choice;
    Matrix matrix;
    BruteForce bruteForce;
    Time time;

    do {
        cout << "\n\n# BRUTE FORCE #" << endl;
        cout << "[1]. Wczytaj macierz z pliku" << endl;
        cout << "[2]. Wygeneruj nowa macierz" << endl;
        cout << "[3]. Wyswietl macierz" << endl;
        cout << "[4]. Wykonaj algorytm Brute Force" << endl;
        cout << "[0]. Wyjscie" << endl;
        cout << "Podaj swoj wybor: ";
        cin >> choice;

        while (choice > 4 || choice < 0) {
            cout << "Podales zla liczbe. Wybierz ponownie: ";
            cin >> choice;
        }

        switch(choice){
            case 1:
                matrix.loadMatrix();
                break;

            case 2:
                matrix.generateMatrix();
                break;

            case 3:
                matrix.displayMatrix();
                break;

            case 4:
                long long int frequency, start, elapsed;
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = time.read_QPC();
                bruteForce.TSP(matrix);
                elapsed = time.read_QPC() - start;
                cout << "\nCzas wykonania algorytmu: " << setprecision(3) << (float)(1000.0 * elapsed/frequency) <<" [ms]." << endl;
                bruteForce.displayResult(matrix);
                //Liczenie czasu w milisekundach
                break;
        }

        if(choice == 0)
            return;

    } while (choice != 0);
}

void Test::branchAndBound(){
    int choice;
    Matrix matrix;
    BranchAndBound branchAndBound;
    Time time;

    do {
        cout << "\n\n# BRANCH AND BOUND #" << endl;
        cout << "[1]. Wczytaj macierz z pliku" << endl;
        cout << "[2]. Wygeneruj nowa macierz" << endl;
        cout << "[3]. Wyswietl macierz" << endl;
        cout << "[4]. Wykonaj algorytm Branch and Bound" << endl;
        cout << "[0]. Wyjscie" << endl;
        cout << "Podaj swoj wybor: ";
        cin >> choice;

        while (choice > 4 || choice < 0) {
            cout << "Podales zla liczbe. Wybierz ponownie: ";
            cin >> choice;
        }

        switch(choice){
            case 1:
                matrix.loadMatrix();
                break;

            case 2:
                matrix.generateMatrix();
                break;

            case 3:
                matrix.displayMatrix();
                break;

            case 4:
                long long int frequency, start, elapsed;
                branchAndBound.createVector(matrix);
                QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
                start = time.read_QPC();
                branchAndBound.algorithm();
                elapsed = time.read_QPC() - start;
                cout << "\nCzas wykonania algorytmu: " << setprecision(3) << (float)(1000.0 * elapsed/frequency) <<" [ms]." << endl;
                //Liczenie czasu w milisekundach
                break;
        }

        if(choice == 0)
            return;

    } while (choice != 0);
}
