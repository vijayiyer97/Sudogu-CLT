//
//  store.cpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/5/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//
#include <cassert>

#include "dlx.hpp"
#include "exception.hpp"

ID::ID(int val, int r, int col) {
    value = val;
    row = r;
    column = col;
}

Store::Node::Node(): member(NONE) {
    left = right = up = down = column = this;
    mandatory = false;
}

Store::Node::Node(bool mand): member(SIZE) {
    left = right = up = down = this;
    column = this;
    size = 0;
    mandatory = mand;
}

Store::Node::Node(struct ID identity, Node* col): member(ID) {
    left = right = up = down = nullptr;
    id = identity;
    column = col;
    column->size++;
    mandatory = false;
}

Store::Node::~Node() {
    
}

ID Store::Node::getID() {
    assert(member == ID);
    return id;
}

int Store::Node::getSize() {
    assert(member == SIZE);
    return size;
}

void Store::Node::hRemove() {
    assert(this->left->right == this);
    assert(this->right->left == this);
    this->left->right = this->right;
    this->right->left = this->left;
}

void Store::Node::vRemove() {
    assert(this->down->up == this);
    assert(this->up->down == this);
    this->down->up = this->up;
    this->up->down = this->down;
    this->column->size--;
}

void Store::Node::hRestore() {
    this->left->right = this;
    this->right->left = this;
    assert(this->left->right == this);
    assert(this->right->left == this);
}

void Store::Node::vRestore() {
    this->down->up = this;
    this->up->down = this;
    this->column->size++;
    assert(this->down->up == this);
    assert(this->up->down == this);
}

void Store::Node::cover() {
    Node* column = this->column;
    column->hRemove();
    for (Node* row = column->down; row != column; row = row->down) {
        for (Node* node = row->right; node != row; node = node->right) {
            node->vRemove();
        }
    }
}

void Store::Node::uncover() {
    Node* column = this->column;
    for (auto* row = column->up; row != column; row = row->up) {
        for (auto* node = row->left; node != row; node = node->left) {
            node->vRestore();
        }
    }
    column->hRestore();
}
