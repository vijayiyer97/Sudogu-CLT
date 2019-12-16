//
//  sudoku.hpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/6/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#ifndef models_sudoku_hpp
#define models_sudoku_hpp

#include <iostream>
#include <string>
#include <vector>

#include "dlx.hpp"

class Dimensions {
public:
    const int rows;
    const int columns;
    const int cells;

    Dimensions(int rows, int columns, int cells);
    Dimensions(const Dimensions& dimensions): rows(dimensions.rows), columns(dimensions.columns), cells(dimensions.cells) { };
};

class Sudoku: public Dimensions, public Constraint {
    int** values{ NULL };
    
    std::string convertToString();
    void initValues();
    std::vector<bool> buildMatrixRow(ID id, bool value);
    void buildSparseMatrix();
public:
    Sudoku(int** const values, int rows = 3, int columns = 3, int cells = 9);
    Sudoku(const Sudoku& sudoku);
    ~Sudoku();
    
    void setCell(ID id);
    int getCell(int row, int column);
    
    friend std::ostream& operator<<(std::ostream& ostream, Sudoku& sudoku);
};

#endif /* models_sudoku_hpp */
