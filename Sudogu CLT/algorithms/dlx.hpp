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
    Matrix matrix{ }; // two dimensional array containing the sparse constraint matrix
    const int mandatory; // maximum allowed mandatory constraints
    const int optional; // maximum allowed optional constraints
    const int options; // number of possibilities for the sparse matrix
    const int sets; // number of constraints sets for the sparse matrix
    
    Constraint(int size, int mandatory, int optional, int options, int sets);
    Constraint(const Constraint& constraint): size(constraint.size), mandatory(constraint.mandatory), optional(constraint.optional), options(constraint.options), sets(constraint.sets) { };
};

struct ID {
    int value;
    int row;
    int column;
    
    ID(int value, int row, int column);
};

class Store {
protected:
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
        enum Union {
            NONE = 0,
            ID,
            SIZE,
        };
        
        const Union member;
        union {
            struct ID id;
            int size;
        };
    };
    
    typedef std::vector<Node*> Nodes;
};

typedef std::vector<ID> Solution;
typedef std::vector<Solution> Solutions;

class DLX: public Store {
private:
    Node* header;
    std::vector<Node*> nodes{ };
    Solution solution{ };
    Solutions solutions{ };
    
    Node* selectColumn();
    bool solve(int limit);
public:
    DLX(Constraint* constraint, int size);
    ~DLX();
    Solutions run(int limit);
};

#endif /* algorithms_dlx_hpp */
