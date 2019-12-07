//
//  sudoku.cpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/6/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#include "sudoku.hpp"
#include "exception.hpp"

Dimensions::Dimensions(int _rows, int _cols, int _cells): rows(_rows), columns(_cols), cells(_cells) { }

Sudoku::Sudoku(int** const arr, int _rows, int _cols, int _cells): Dimensions(_rows, _cols, _cells), Constraint(cells * cells, 4, 0 , cells * cells * cells, 4 * cells * cells) {
    initValues();
    
    for (int i = 0; i < cells; i++) {
        for (int j = 0; j < cells; j++) {
            int value = arr[i][j];
            try {
                if (value < 0) {
                    throw Exception(INVALID_INPUT);
                }
            } catch (Exception except) {
                switch (except.code) {
                    case INVALID_INPUT: value = 0; break;
                    default: throw except;
                }
            }
            values[i][j] = value;
        }
    }
}

Sudoku::Sudoku(const Sudoku& sudoku): Dimensions(sudoku), Constraint(sudoku) {
    initValues();
    for (int i = 0; i < cells; i++) {
        for (int j = 0; j < cells; j++) {
            values[i][j] = sudoku.values[i][j];
        }
    }
}

void Sudoku::initValues() {
    values = new int* [cells]{ };
    for (int i = 0; i < cells; i++) {
        values[i] = new int[cells]{ };
    }
}

static long int pow(int base, int exp) {
    long int value = 1;
    for (int i = 0; i < exp; i++) {
        value *= base;
    }
    
    return value;
}

static int getLength(int size) {
    int digits = 0;
    int prev;
    int next = size;
    while (next > 0) {
        prev = next;
        next = prev / 10;
        digits++;
    }
    if (digits == 0) {
        throw Exception(SIZE);
    }
    if (digits == 1) {
        return (size - 1) * 2 + 1;
    } else {
        int temp = size;
        int len = 18;
        int count, extra;
        for (int i = digits; i > 1; i--) {
            extra = temp % pow(10, i - 1);
            count = temp - int(pow(10, i - 1)) - extra;
            len += (count + extra) * (i + 1) + i;
            temp -= count + extra + 1;
        }
        return len;
    }
}

std::string Sudoku::stringConvert() {
    try {
        int len = getLength(cells);
        std::string divider = "|" + std::string(len, '-') + "|\n";
        std::string str = "";
        for (int i = 0; i < cells; i++) {
            if (i % rows == 0) {
                str += divider;
            } else {
                for (int j = 0; j < cells; j++) {
                    if (j % columns == 0) {
                        str += "|";
                    } else {
                        str += " ";
                    }
                    
                    int value = values[i][j];
                    if (value != 0) {
                        str += std::to_string(value);
                    } else {
                        str += "o";
                    }
                }
                str += "|\n";
            }
        }
        
        str += divider;
        return str;
    } catch (Exception except) {
        switch(except.code) {
            case SIZE: return "";
            default: throw except;
        }
    }
}

std::vector<bool> Sudoku::buildMatrixRow(ID id) {
    std::vector<bool> exact_cover{ };
    exact_cover.resize(sets);
    int constraint_1 = id.row * cells + id.column;
    int constraint_2 = id.row * cells + (id.value - 1) + size;
    int constraint_3 = id.column * cells + (id.value - 1) + 2 * size;
    int constraint_4 = (id.row - (id.row % rows) + id.column / columns) * cells + (id.value - 1) + 3 * size;
    exact_cover[constraint_1] = 1;
    exact_cover[constraint_2] = 1;
    exact_cover[constraint_3] = 1;
    exact_cover[constraint_4] = 1;
    
    return exact_cover;
}

void Sudoku::buildSparseMatrix() {
    for (int i = 0; i < cells; ++i) {
        for (int j = 0; j < cells; ++j) {
            int value = values[i][j];
            if (value == 0) {
                for (int k = 0; k < cells; ++k) {
                    ID id{ k + 1, i, j };
                    std::vector<bool> row = buildMatrixRow(id);
                    matrix.push_back(row);
                }
            } else {
                ID id{ value, i, j };
                std::vector<bool> row = buildMatrixRow(id);
                matrix.push_back(row);
            }
        }
    }
}


void Sudoku::setCell(int row, int col, int val) {
    values[row][col] = val;
}

int Sudoku::getCell(int row, int col) {
    return values[row][col];
}

std::ostream& operator <<(std::ostream& ostream, Sudoku& sudoku) {
    ostream << sudoku.stringConvert();
    return ostream;
}
