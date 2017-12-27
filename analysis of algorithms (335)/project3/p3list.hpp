//
//  p3list.hpp
//  aoa_hw3
//
//  Created by Muhammet Uçan on 19.11.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#ifndef p3list_hpp
#define p3list_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include "p3char.hpp"

class List {
    vector<BookChar> container;
public:
    List() {};
    vector<BookChar>& getContainer() {return container;}
    bool insertion();
    bool readForlookup();
    // the param is the list for look up
    void lookup(List&);
    // if bool true reading is for insertion
    bool readFromFile(string,bool);
};

#endif /* p3list_hpp */
