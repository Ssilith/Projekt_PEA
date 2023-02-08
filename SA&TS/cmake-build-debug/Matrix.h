//
// Created by Katarzyna Hajduk on 19.10.2022.
//

#ifndef PEA_MATRIX_H
#define PEA_MATRIX_H
#include <string>

class Matrix {
private:
    int size;
    int **matrix;

public:
    Matrix();
    ~Matrix();
    void loadMatrix();
    void displayMatrix();
    void generateMatrix();
    int getSize();
    int getValue(int x, int y);

    void deleteMatrix();
};


#endif //PEA_MATRIX_H
