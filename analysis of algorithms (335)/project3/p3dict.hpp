//
//  p3dict.hpp
//  aoa_hw3
//
//  Created by Muhammet Uçan on 19.11.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#ifndef p3dict_hpp
#define p3dict_hpp

#include <stdio.h>
#include "p3char.hpp"
#define TABLE_SIZE 131071

class HashNode {
    unsigned long key;
    BookChar value;
public:
    HashNode(const unsigned long &key, const BookChar &value) {
        this->key = key;
        this->value = value;
    }
    unsigned long getKey() const {
        return key;
    }
    BookChar getValue() const {
        return value;
    }
    void setValue(BookChar value) {
        this->value = value;
    }
};


class HashMap {
    HashNode **table;
    int totalCollision;
    double avColFor1k, avColFor10k, avColFor100k, avColForAll;
public:
    HashMap();
    ~HashMap();
    double getAverages(int=0);
    BookChar get(unsigned long key);
    int put(unsigned long key,const BookChar& value);
    unsigned long hashFunc(unsigned long key);
    unsigned long quadraticProbe(unsigned long,int&);
    bool readFromFile(string,bool);
    bool insertion();
    bool lookup();
};
#endif /* p3dict_hpp */
