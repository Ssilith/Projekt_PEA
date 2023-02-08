//
// Created by Katarzyna Hajduk on 19.10.2022.
//

#include "Test.h"
#include <iostream>

using namespace std;

void Test::simulatedAnnealing(){
    int choice;
    double alpha = 0.99;
    int timeToStop = 10;
    int cooling = 1;
    double beta = 0.001;

    do {
        cout << "\n\n# SIMULATED ANNEALING #" << endl;
        cout << "[1]. Wczytaj macierz z pliku" << endl;
        cout << "[2]. Wygeneruj nowa macierz" << endl;
        cout << "[3]. Wyswietl macierz" << endl;
        cout << "[4]. Wykonaj algorytm Simulated Annealing" << endl;
        cout << "[5]. Wprowadz kryterium stopu" << endl;
        cout << "[6]. Wprowadz wspolczynnik zmiany temperatury" << endl;
        cout << "[7]. Wybierz sposob schladzania" << endl;
        cout << "[0]. Wyjscie" << endl;
        cout << "Podaj swoj wybor: ";
        cin >> choice;

        while (choice > 7 || choice < 0) {
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
                simulatedannealing.createMatrix(matrix);
                simulatedannealing.simulateAnnealing(timeToStop, alpha, cooling, beta);
                break;

            case 5:
                cout << "Podaj czas w sekundach: ";
                cin >> timeToStop;
                break;

            case 6:
                cout << "Podaj wspolczynnik zmiany temperatury: ";
                cin >> alpha;
                break;

            case 7:
                cout << "Podaj sposob schladzania: " << endl;
                cout << "[1]. T(i+1) = a * T(i)" << endl;
                cout << "[2]. T(i+1) = (a ^ k) * T(i), gdzie k to liczba epok" << endl;
                cout << "[3]. T(i+1) = (T(i) / (a + b * k)), gdzie b to wspolczynik beta" << endl;
                cout << "Wybor: ";
                cin >> cooling;

                if(cooling > 3 || cooling < 1)
                    cooling = 1;

                if(cooling == 3) {
                    cout << "Podaj wspolczynnik spelniajacy warunek beta << 1: ";
                    cin >> beta;
                }
                break;
        }

        if(choice == 0)
            return;

    } while (choice != 0);
}

void Test::tabuSearch(){
    int choice;
    int timeToStop = 10;
    int neigbourhood = 1;

    do {
        cout << "\n\n# TABU SEARCH #" << endl;
        cout << "[1]. Wczytaj macierz z pliku" << endl;
        cout << "[2]. Wygeneruj nowa macierz" << endl;
        cout << "[3]. Wyswietl macierz" << endl;
        cout << "[4]. Wykonaj algorytm Tabu Search" << endl;
        cout << "[5]. Wprowadz kryterium stopu" << endl;
        cout << "[6]. Wybierz definicje sasiedztwa" << endl;
        cout << "[0]. Wyjscie" << endl;
        cout << "Podaj swoj wybor: ";
        cin >> choice;

        while (choice > 6 || choice < 0) {
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
                tabusearch.createMatrix(matrix);
                tabusearch.tabuSearch(timeToStop, neigbourhood);
                break;

            case 5:
                cout << "Podaj czas w sekundach: ";
                cin >> timeToStop;
                cout << "Czas stopu wyniosi: " << timeToStop << endl;
                break;

            case 6:
                cout << "Wybierz sasiedztwo: " << endl;
                cout << "[1]. Swap" << endl;
                cout << "[2]. Insert" << endl;
                cout << "[3]. Invert" << endl;
                cout << "Wybor: ";
                cin >> neigbourhood;

                if(neigbourhood > 3 || neigbourhood < 1)
                    neigbourhood = 1;
                break;
        }

        if(choice == 0)
            return;

    } while (choice != 0);
}
