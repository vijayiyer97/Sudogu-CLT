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
protected:
    const int rows;
    const int columns;
    const int cells;
public:
    Dimensions(int rows, int columns, int cells);
    Dimensions(const Dimensions& dimensions): rows(dimensions.rows), columns(dimensions.columns), cells(dimensions.cells) { };
};

class Sudoku: protected Dimensions, public Constraint {
    int** values{ NULL };
    
    std::string stringConvert();
    void initValues();
    std::vector<bool> buildMatrixRow(ID id);
    void buildSparseMatrix();
public:
    Sudoku(int** const values, int rows = 3, int columns = 3, int cells = 9);
    Sudoku(const Sudoku& sudoku);
    ~Sudoku();
    
    void setCell(int row, int column, int value);
    int getCell(int row, int column);
    
    friend std::ostream& operator <<(std::ostream& ostream, Sudoku& sudoku);
};

#endif /* models_sudoku_hpp */
