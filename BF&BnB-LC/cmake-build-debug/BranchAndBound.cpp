//
// Created by Katarzyna Hajduk on 04.11.2022.
//

#include <iostream>
#include <algorithm>
#include "BranchAndBound.h"

using namespace std;

BranchAndBound::BranchAndBound(){
    size = 0;
}

BranchAndBound::~BranchAndBound(){
    size = 0;
    matrix.clear();
}

void BranchAndBound::createVector(Matrix mat){
    //Wpisywanie matrycy do wektora, na którym potem będę operować
    size = mat.getSize();
    matrix.resize(size);

    for (int i = 0; i < size; i++)
        matrix[i].resize(size);

    for(int i = 0; i < mat.getSize(); i++){
        for(int j = 0; j < mat.getSize(); j++)
            matrix[i][j] = mat.getValue(i, j);
    }
}

int BranchAndBound::matrixReduction(vector<vector<int>>& matrix) {
    //Usuwanie wartości w rzędach i kolumnach, aby uzyskać co najmniej jedno 0 w każdym
    int sum_min = 0;
    int min_value = INT_MAX;

    //Wiersze
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] < min_value && matrix[i][j] != -1)
                min_value = matrix[i][j];
        }

        if (min_value != INT_MAX && min_value != -1) {
            sum_min += min_value;
            for (int j = 0; j < size; j++) {
                if (matrix[i][j] != -1)
                    matrix[i][j] -= min_value;
            }
            min_value = INT_MAX;
        }
    }

    //Kolumny
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[j][i] < min_value)
                min_value = matrix[j][i];
        }

        if (min_value != INT_MAX && min_value != -1) {
            sum_min += min_value;
            for (int j = 0; j < size; j++) {
                if (matrix[j][i] != -1)
                    matrix[j][i] -= min_value;
            }
            min_value = INT_MAX;
        }
    }
    //Koszt po zredukowaniu
    return sum_min;
}

int BranchAndBound::reducedCost(int row, int column, vector<vector<int>>& matrix, int reduced_cost) {
    //Liczenie kosztu dla danego węzła po "usunięciu" danej kolumny i rzędu
    reduced_cost += matrix[row][column];
    newMatrix(row, column, matrix);
    reduced_cost += matrixReduction(matrix);
    return reduced_cost;
}

void BranchAndBound::newMatrix(int row, int column, vector<vector<int>>& matrix) {
    //"Usuwanie" danego rzędu i kolumny
    for (int i = 0; i < size; i++)
        matrix[row][i] = -1;

    for (int i = 0; i < size; i++)
        matrix[i][column] = -1;

    matrix[column][0] = -1; //Blokowanie powrotu
}

bool BranchAndBound:: checkIfInSeq(int i, vector<int> sequence){
    //Sprawdzenie, czy dane miasto już zostało odwiedzone
    for(int j = 0; j < sequence.size(); j++){
        if(i == sequence.at(j))
            return true;
    }
    return false;
}

void BranchAndBound::displaySolution(vector<int> reduced_cost, vector<vector<int>> temp_sequence, int position){
    //Wyświetlanie wyniku
    cout << "Minimalne tsp: " << reduced_cost[position] << endl;
    for (int i = 0; i < temp_sequence[position].size(); i++)
        cout << temp_sequence[position].at(i) << " -> ";
    cout << "0";
    cout << endl;
}

void BranchAndBound::algorithm(){
    //Główny algorytm
    vector<vector<int>> matrix_zero; //Dodatkowa matryca, by nie zmieniać głównej
    matrix_zero = matrix;

   int cost = matrixReduction(matrix_zero); //Liczymy koszt po zredukowaniu

    vector<vector<vector<int>>> temp_matrix; //Vector 2-wymiarowych tablic
    vector<vector<int>> temp_sequence; //Vector sekwencji dla danej matrycy
    vector<int> reduced_cost; //Vector kosztów

    temp_matrix.push_back(matrix_zero); //Wrzucamy "zerową" matrycę razem tmpMat kosztem i dotychczasową sekwencją
    reduced_cost.push_back(cost);
    temp_sequence.push_back(vector<int>(1,0)); //Sekwencje wypełniamy jedną wartością równą 0

    int tmpVertex = 0; //Tymczasowy wierzchołek (rząd)
    int tmpMat = 0; //Numer macierzy, z której korzystamy

    while(true) { //Wychodzimy z pętli w if, bo nie wiadomo ile iteracji będzie tak naprawdę potrzebnych
        for (int i = 1; i < size; i++) { //Zmiana kolumn
            bool change = checkIfInSeq(i, temp_sequence[tmpMat]); //Sprawdzenie, jakie wierzchołki zostały odwiedzone

            if (!(change) && temp_matrix[tmpMat][tmpVertex][i] != -1) {
                vector<vector<int>> tmp_matrix = temp_matrix[tmpMat];

                temp_matrix.push_back(tmp_matrix);
                temp_sequence.push_back(temp_sequence[tmpMat]); //Kopiowanie dotychczasowej sekwencji
                temp_sequence.back().push_back(i); //I dodanie kolejnego wierzchołka

                //Liczenie kosztu po "usunięciu" danego rzędu i kolumny
                int cost = reducedCost(tmpVertex, i, temp_matrix.back(), reduced_cost[tmpMat]);
                reduced_cost.push_back(cost);
            }
        }
        //Wrzucamy wartość maksymalną, bo wartość w kolejnym rzędzie na pewno nie będzie mniejsza
        reduced_cost[tmpMat] = INT_MAX;

        //Uzyskujemy pozycje gdzie jest minimalny element
        int	position = (int)(min_element(reduced_cost.begin(), reduced_cost.end()) - reduced_cost.begin());

        if (temp_sequence[position].size() == size) { //Jeżeli dotarliśmy do końca to wyświetlenie wyniku
            displaySolution(reduced_cost, temp_sequence, position);
            return;
        }

        //Jeżeli nie to nowym wierszem jest pozycja min elementu
        tmpMat = position;
        tmpVertex = temp_sequence[tmpMat].back();
    }
}
