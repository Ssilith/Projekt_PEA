//
// Created by Katarzyna Hajduk on 04.11.2022.
//

#ifndef PEA_BRANCHANDBOUND_H
#define PEA_BRANCHANDBOUND_H
#include "Matrix.h"
#include <vector>

using namespace std;

class BranchAndBound {
private:
    int size;
    vector<vector<int>> matrix;

public:
    BranchAndBound();
    ~BranchAndBound();
    void createVector(Matrix mat);
    void algorithm();
    int matrixReduction(vector<vector<int>> &matrix);
    void newMatrix(int row, int column, vector<vector<int>> &matrix);
    int reducedCost(int row, int column, vector<vector<int>> &matrix, int reduced_cost);
    bool checkIfInSeq(int i, vector<int> sequence);
    void displaySolution(vector<int> reduced_cost, vector<vector<int>> temp_sequence, int position);
};


#endif //PEA_BRANCHANDBOUND_H
