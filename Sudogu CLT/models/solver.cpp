//
//  solver.cpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/7/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#include "solver.hpp"

Solver::Solver(Sudoku other): sudoku(other) { }
Solver::Solver(int** const vals, int rows, int cols, int cells): sudoku(vals, rows, cols, cells) { }

Sudoku Solver::convertToSudoku(Solution solution) {
    Sudoku solved{ sudoku };
    for (auto id: solution) {
        solved.setCell(id);
    }
    return solved;
}

Result Solver::search() {
    Result result{ };
    Constraint* constraint = &sudoku;
    DLX dlx{ constraint, sudoku.cells };
    Solutions solutions = dlx.run();
    for (auto solution: solutions) {
        Sudoku solved{ convertToSudoku(solution) };
        result.solutions.push_back(solved);
        ++result.size;
    }
    
    return result;
}
