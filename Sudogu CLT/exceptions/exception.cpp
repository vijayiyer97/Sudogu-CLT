//
//  exception.cpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/5/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#include <iostream>
#include <string>

#include "exception.hpp"

Exception::Exception(Code type) {
    code = type;
    std::string message;
    
    switch (code) {
        case NORMAL: message = "Program executed normally."; break;
        case ERROR: message = "Program encountered an error."; break;
            
        case OVERRIDE: message = "Program must override virtual function."; break;
        case NULL_PTR: message = "Null pointer error encountered."; break;
        case ACCESS_FORBID: message = "Undefined member access forbidden"; break;
            
        case SIZE: message = "Invalid sudoku size input."; break;
        case UNSOLVABLE: message = "Sudoku cannot be solved."; break;
        case NO_NODES: message = "Toroidal matrix has no nodes"; break;
        
        default:
            message = "";
    }
    
    std::cout << message << std::endl;
}
