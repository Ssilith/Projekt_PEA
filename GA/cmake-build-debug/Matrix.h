//
// Created by Katarzyna Hajduk on 21.12.2022.
//

#ifndef PEA_3_MATRIX_H
#define PEA_3_MATRIX_H

#include <string>

class Matrix {
private:
    int size;
    int **matrix;

public:
    void loadMatrix();

    void displayMatrix();

    int getSize();

    int getValue(int x, int y);
};


#endif //PEA_3_MATRIX_H
