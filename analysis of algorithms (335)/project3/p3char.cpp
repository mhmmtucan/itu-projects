//
//  p3char.cpp
//  aoa_hw3
//
//  Created by Muhammet Uçan on 19.11.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#include "p3char.hpp"

unsigned long BookChar::generateKey() {
    string lineNoStr = to_string(lineNo),indexStr = to_string(index);
    // in order to diff 1 from 10 add 0 before 1
    if (lineNo < 10) {
        lineNoStr = "0" + lineNoStr;
    }
    if (index < 10) {
        indexStr = "0" + indexStr;
    }
    return stoul(to_string(pageNo) + lineNoStr + indexStr);
}
