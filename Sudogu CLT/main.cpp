//
//  main.cpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/5/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#include <iostream>

#include "solver.hpp"
#include "exception.hpp"

int main(int argc, const char * argv[]) {
    std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!
    int array[9][9] = {
//        {0, 0, 0,  0, 0, 0,  0, 0, 0},
//        {0, 0, 0,  0, 0, 0,  0, 0, 0},
//        {0, 0, 0,  0, 0, 0,  0, 0, 0},
//
//        {0, 0, 0,  0, 0, 0,  0, 0, 0},
//        {0, 0, 0,  0, 0, 0,  0, 0, 0},
//        {0, 0, 0,  0, 0, 0,  0, 0, 0},
//
//        {0, 0, 0,  0, 0, 0,  0, 0, 0},
//        {0, 0, 0,  0, 0, 0,  0, 0, 0},
//        {0, 0, 0,  0, 0, 0,  0, 0, 0},
        {0, 0, 0,  7, 0, 0,  0, 0, 0},
        {1, 0, 0,  0, 0, 0,  0, 0, 0},
        {0, 0, 0,  4, 3, 0,  2, 0, 0},

        {0, 0, 0,  0, 0, 0,  0, 0, 6},
        {0, 0, 0,  5, 0, 9,  0, 0, 0},
        {0, 0, 0,  0, 0, 0,  4, 1, 8},

        {0, 0, 0,  0, 8, 1,  0, 0, 0},
        {0, 0, 2,  0, 0, 0,  0, 5, 0},
        {0, 4, 0,  0, 0, 0,  3, 0, 0},

    };
    int iSize = sizeof(array) / sizeof(array[0]);
    int jSize = sizeof(array[0]) / sizeof(int);
    int** values;
    values = new int* [iSize];
    for (int i = 0; i < iSize; i++) {
        values[i] = new int [jSize];
    }
    for (int i = 0; i < iSize; i++) {
        for (int j = 0; j < jSize; j++) {
            values[i][j] = array[i][j];
        }
    }
    
    try {
        Sudoku sudoku{ values };
        
        std::cout << sudoku << std::endl;
        
        Solver solver{ sudoku };
        Result result = solver.search(1);
        
        std::cout << result.solutions[0] << std::endl;
        
    } catch (Exception except) { }
    
    return 0;
}
