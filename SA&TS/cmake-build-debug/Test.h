//
// Created by Katarzyna Hajduk on 19.10.2022.
//

#ifndef PEA_TEST_H
#define PEA_TEST_H
#include "SimulatedAnnealing.h"
#include "Matrix.h"
#include "TabuSearch.h"

class Test {
private:
    Matrix matrix;
    SimulatedAnnealing simulatedannealing;
    TabuSearch tabusearch;

public:
    void simulatedAnnealing();
    void tabuSearch();
};


#endif //PEA_TEST_H
