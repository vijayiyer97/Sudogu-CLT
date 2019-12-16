//
//  solver.hpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/7/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#ifndef models_solver_hpp
#define models_solver_hpp

#include <vector>

#include "sudoku.hpp"
#include "dlx.hpp"

struct Result {
    std::vector<Sudoku> solutions;
    unsigned size = 0;
};

class Solver {
    Sudoku sudoku;
    
    Sudoku convertToSudoku(Solution solution);
public:
    Solver(Sudoku sudoku);
    Solver(int** const values, int rows = 3, int columns = 3, int cells = 9);
    
    Result search(int limit);
};
#endif /* models_solver_hpp */
