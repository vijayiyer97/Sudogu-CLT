//
//  exception.hpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/5/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#ifndef exceptions_exception_hpp
#define exceptions_exception_hpp

enum Code {
    NORMAL = 0,
    ERROR = -1,
    
    OVERRIDE = 100,
    NULL_PTR,
    ACCESS_FORBID,
    NOT_EXACT_COVER,
    
    INVALID_INPUT = 200,
    SIZE,
    UNSOLVABLE,
    NO_NODES,
};

class Exception {
public:
    Code code;
    
    Exception(Code code);
};

#endif /* exceptions_exception_hpp */
