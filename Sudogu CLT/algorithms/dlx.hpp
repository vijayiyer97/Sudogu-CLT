//
//  dlx.hpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/5/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#ifndef algorithms_dlx_hpp
#define algorithms_dlx_hpp

#include <vector>

typedef std::vector<std::vector<bool>> Matrix;

class Constraint {
public:
    const int size; // size of the exact cover
    Matrix matrix; // two dimensional array containing the sparse constraint matrix
    
    Constraint(int size, int mandatory, int optional, int options, int sets);
protected:
    const int mandatory; // maximum allowed mandatory constraints
    const int optional; // maximum allowed optional constraints
public:
    const int options; // number of possibilities for the sparse matrix
    const int sets; // number of constraints sets for the sparse matrix
};

class Store {
protected:
    struct ID {
        int value;
        int row;
        int column;
        
        ID(int value, int row, int column);
    };
    
    struct Node {
        Node* left;
        Node* right;
        Node* up;
        Node* down;
        Node* column;
        bool mandatory;
        
        Node();
        Node(bool mandatory);
        Node(ID id, Node* column);
        ~Node();
        
        ID getID();
        int getSize();
        
        void hRemove();
        void vRemove();
        void hRestore();
        void vRestore();
        
        void cover();
        void uncover();
    private:
        int member;
        union {
            ID id;
            int size;
        };
    };
    
    typedef std::vector<Node*> Nodes;
};

class DLX: public Store {
public:
    typedef std::vector<ID> Solution;
private:
    Node* header;
    std::vector<Node*> nodes{ };
    Solution solution{ };
    
    Node* selectColumn();
    bool solve();
public:
    DLX(Constraint constraint, int size);
    ~DLX();
    Solution run();
};

#endif /* algorithms_dlx_hpp */
