//
//  constraint.cpp
//  Sudogu CLT
//
//  Created by Vijay Iyer on 12/7/19.
//  Copyright © 2019 Bananna Companay. All rights reserved.
//

#include "dlx.hpp"
#include "exception.hpp"

Constraint::Constraint(int _size, int _mandatory, int _optional, int _options, int _sets): size(_size), mandatory(_mandatory), optional(_optional), options(_options), sets(_sets) {
    if (mandatory < 0) {
        throw Exception(NOT_EXACT_COVER);
    }
}
