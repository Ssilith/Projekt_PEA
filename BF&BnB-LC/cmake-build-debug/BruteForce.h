//
// Created by Katarzyna Hajduk on 20.10.2022.
//

#ifndef PEA_BRUTEFORCE_H
#define PEA_BRUTEFORCE_H
#include "Matrix.h"

class BruteForce {
private:
    int *path{};
    int distance{};
    int minDistance{};
    int *array{};

public:
    BruteForce();
    ~BruteForce();
    void TSP(Matrix matrix);
    void displayResult(Matrix matrix);
};


#endif //PEA_BRUTEFORCE_H
