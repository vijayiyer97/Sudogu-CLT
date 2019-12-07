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

Store::ID::ID(int val, int r, int c) {
    value = val;
    row = r;
    column = c;
}

Store::Node::Node() {
    left = right = up = down = column = nullptr;
    mandatory = false;
}

Store::Node::Node(bool mand) {
    left = right = up = down = nullptr;
    column = this;
    size = 0;
    mandatory = mand;
}

Store::Node::Node(ID i, Node* col) {
    left = right = up = down = nullptr;
    id = i;
    column = col;
    column->size++;
    mandatory = false;
}

Store::Node::~Node() {
    
}

Store::ID Store::Node::getID() {
    if (member == 0) {
        return id;
    }
    throw Exception(ACCESS_FORBID);
}

int Store::Node::getSize() {
    if (member == 1) {
        return size;
    }
    throw Exception(ACCESS_FORBID);
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
    for (auto* row = column->down; row != column; row = row->down) {
        for (auto right = row->right; right != row; right = right->right) {
            right->vRemove();
        }
    }
}

void Store::Node::uncover() {
    Node* column = this->column;
    for (auto* row = column->up; row != column; row = row->up) {
        for (auto left = row->left; left != row; left = left->left) {
            right->vRestore();
        }
    }
    column->hRestore();
}
