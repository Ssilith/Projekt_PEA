//
// Created by Katarzyna Hajduk on 19.10.2022.
//

#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

Matrix::Matrix(){}

Matrix::~Matrix(){}

void Matrix::loadMatrix(){ //Wczytanie matrycy
    string name;
    cout << "Podaj nazwe pliku (pamietaj o rozszerzeniu .atsp): ";
    cin >> name;

    ifstream file;
    file.open("Dane/" + name);

    if (file.is_open() == 1){ //Sprawdzanie czy udalo sie otworzyc plik
        bool tmp = true; //Znajdowanie size
        while(tmp){
            file >> name;
            if (name == "DIMENSION:") {
                file >> size;
                tmp = false;
            }
        }

        matrix = new int *[size];

        for (int i = 0; i < size; i++)
            matrix[i] = new int [size]; //Dynamiczne tworzenie matrycy

        int counter = 0; //Licznik rzedow
        while (true){
            file >> name;
            if(name == "EDGE_WEIGHT_SECTION"){
                while (name != "EOF") {
                    for (int i = 0; i < size; i++) { //Licznik kolumn
                        file >> name;
                        if (name != "EOF") {

                            istringstream iss(name);
                            iss >> matrix[counter][i]; //Wpisywanie poszczegolnych wartosci

                            if (counter == i)
                                matrix[counter][i] = 100000000; //Od razu zmieniam po przekatnej na jedna wartosc
                        }
                    }
                    counter++;
                }
                break;
            }
        }
    }
    else //W razie bledu wyswietla komunikat
        cout << "Blad odczytu pliku!" << endl;

    file.close(); //Zamkniecie pliku
}

void Matrix::displayMatrix(){
    cout << "Matryca miast:"<<endl;

    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
}

int Matrix::getSize(){ //Funkcja pomocnicza zwracajaca wielkosc macierzy
    return size;
}

int Matrix::getValue(int x, int y){ //Funkcja pomocnicza zwracajaca wielkosc macierzy
    return matrix[x][y];
}

void Matrix::generateMatrix(){ //Generowanie tablicy o podanym rozmiarze i podanym zakresie
    cout << "Podaj wielkosc macierzy: ";
    cin >> size;

    int x, y;
    cout << "Podaj pierwszy zakres macierzy: ";
    cin >> x;
    cout << "Podaj drugi zakres macierzy: ";
    cin >> y;

    if (x > y){
        int tmp = x;
        x = y;
        y = tmp;
    }

    matrix = new int *[size];
    for (int i = 0; i < size; i++)
        matrix[i] = new int [size]; //Dynamiczne tworzenie matrycy

    for (int i = 0; i < size; i++){ //Uzupelnienie danymi z pliku
        for (int j = 0; j < size; j++){
            if(i != j)
                matrix[i][j] = rand() % (y - x + 1) + x;

            else
                matrix[i][j] = 100000000;
        }
    }
}

