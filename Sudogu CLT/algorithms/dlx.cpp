//
//  dlx.cpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/5/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#include "dlx.hpp"
#include "exception.hpp"

DLX::DLX(Constraint constraint, int cells) {
    const Matrix matrix = constraint.matrix;
    const int size = constraint.size;
    const int options = constraint.options;
    const int sets = constraint.sets;
    
    header = new Node{ };
    nodes.push_back(header);
    Nodes temp_col;
    Nodes header_col;
    Node* node = header;
    for (int i = 0; i < sets; ++i) {
        auto* col = new Node{ true };
        nodes.push_back(col);
        node->right = col;
        col->left = node;
        node = col;
        temp_col.push_back(col);
        header_col.push_back(col);
    }
    node->right = header;
    header->left = node;
    
    ID id { 0, 1, 1 };
    for (int i = 0; i < options; ++i) {
        Node* temp_row{ nullptr };
        Node* header_row{ nullptr };
        
        if (i != 0 && i % size == 0) {
            id.value -= cells - 1;
            id.row++;
            id.column -= cells - 1;
        } else if (i != 0 && cells == 0) {
            id.value -= cells - 1;
            id.column++;
        } else {
            id.value++;
        }
        
        for (int j = 0; j < sets; ++j) {
            if (matrix[i][j]) {
                auto* node = new Node{ id, header_col[j]};
                nodes.push_back(node);
                temp_col[j]->down = node;
                node->up = temp_col[j];
                temp_col[j]= node;
                if (temp_row) {
                    temp_row->right = node;
                    node->left = temp_row;
                    temp_row = node;
                } else {
                    temp_row = header_row = node;
                }
            }
        }
        temp_row->right = header_row;
        header_row->left = temp_row;
    }
    
    for (int i = 0; i < sets; ++i) {
        temp_col[i]->down = header_col[i];
        header_col[i]->up = temp_col[i];
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
            throw Exception(NO_NODES);
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
    
    try {
        Node* column = selectColumn();
        column->cover();
        
        for (auto row = column->down; row != column; row = row->down) {
            solution.push_back(row->getID());
            
            for (auto right = row->right; right != row; right = right->right) {
                right->cover();
            }
            
            if (solve()) {
                return true;
            }
            
            solution.pop_back();
            
            for (auto left = row->left; left != row; left = left->left) {
                left->uncover();
            }
        }
        
        column->uncover();
        return false;
        
    } catch (Exception except) {
        switch (except.code) {
            case NO_NODES: return false;
            default: throw except;
        }
    }
}
