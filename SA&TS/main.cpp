#include <iostream>
#include "cmake-build-debug/Test.h"

using namespace std;

int main(){
    Test test;
    int choice = 0;

    cout << "Katarzyna Hajduk 259189" << endl;

    do {
        cout << "\n\n# MENU #" << endl;
        cout << "[1]. Testowanie algorytmu Symulowanego Wyzarzania" << endl;
        cout << "[2]. Testowanie algorytmu Tabu Search" << endl;
        cout << "[0]. Wyjscie" << endl;
        cout << "Podaj swoj wybor: ";
        cin >> choice;

        while (choice > 2 || choice < 0) {
            cout << "Podales zla liczbe. Wybierz ponownie: ";
            cin >> choice;
        }

        switch(choice){
            case 1:
                test.simulatedAnnealing();
                break;

            case 2:
                test.tabuSearch();
                break;
        }
    } while (choice != 0);

    return 0;
}
