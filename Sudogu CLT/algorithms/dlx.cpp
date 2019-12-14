//
//  dlx.cpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/5/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#include "dlx.hpp"
#include "exception.hpp"

DLX::DLX(Constraint* constraint, int cells) {
    const Matrix matrix = constraint->matrix;
    const int size = constraint->size;
    const int options = constraint->options;
    const int sets = constraint->sets;
    
    header = new Node{ };
    header->left = header;
    header->right = header;
    header->down = header;
    header->up = header;
    header->column = header;
    
    Node* temp = header;
    for (int i = 0; i < sets; ++i) {
        auto* col = new Node{ true };
        col->up = col;
        col->down = col;
        col->right = header;
        temp->right = col;
        col->left = temp;
        temp = col;
    }
    temp->right = header;
    temp->right->left = temp;
    
    
    ID id { 0, 1, 1 };
    for (int i = 0; i < options; ++i) {
        Node* top = header->right;
        Node* prev = NULL;
        
        if (i != 0 && i % size == 0) {
            id.value -= cells - 1;
            id.row++;
            id.column -= cells - 1;
        } else if (i != 0 && i % cells == 0) {
            id.value -= cells - 1;
            id.column++;
        } else {
            id.value++;
        }
        
        for (int j = 0; j < sets; ++j, top = top->right) {
            if (matrix[i][j]) {
                auto* node = new Node { id, top };
                if (prev == NULL) {
                    prev = node;
                    prev->right = node;
                }
                node->left = prev;
                node->right = prev->right;
                node->right->left = node;
                node->left->right = node;
                
                node->down = top;
                node->up = top->up;
                node->up->down = node;
                node->down->up = node;
                
                if (top->down == top) {
                    top->down = node;
                }
                
                prev = node;
            }
        }
    }
}

DLX::~DLX() {
    for (auto node: nodes) {
        delete node;
    }
}

Store::Node* DLX::selectColumn() {
    Node* current = header->right;
    int min_size = current->getSize();
    Node* next = current;
    while (current != header) {
        int size = current->getSize();
        
        if (size == 0) {
            return header;
        } else if (size == 1) {
            return current;
        } else if (size < min_size) {
            min_size = size;
            next = current;
        }
        
        current = current->right;
    }
    
    return next;
}

bool DLX::solve() {
    if (header->right == header) {
        return true;
    }
    
    Node* column = selectColumn();
    
    if (column == header) {
        return false;
    }
    
    column->cover();
    
    for (auto row = column->down; row != column; row = row->down) {
        solution.push_back(row->getID());
        
        for (auto node = row->right; node != row; node = node->right) {
            node->cover();
        }
        
        if (solve()) {
            solutions.push_back(solution);
        }
        
        solution.pop_back();
        
        for (auto node = row->left; node != row; node = node->left) {
            node->uncover();
        }
    }
    
    column->uncover();
    return false;
}

Solutions DLX::run() {
    solve();
    
    if (solutions.size() == 0) {
        throw Exception(UNSOLVABLE);
    }
    
    return solutions;
}
