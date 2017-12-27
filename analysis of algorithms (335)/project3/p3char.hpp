//
//  p3char.hpp
//  aoa_hw3
//
//  Created by Muhammet Uçan on 19.11.2017.
//  Copyright © 2017 Muhammet Uçan. All rights reserved.
//

#ifndef p3char_hpp
#define p3char_hpp
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <cstdlib>

class BookChar {
    int pageNo;
    int lineNo;
    int index;
    char c;
    unsigned long key;
    bool isInsertion;
public:
    BookChar() {
        pageNo = 0; lineNo=0; index=0; c='\0'; key=0;
        isInsertion = true;
    }
    BookChar(bool isInsertion) {
        pageNo = 0; lineNo=0; index=0; c='\0'; key=0;
        this->isInsertion = isInsertion;
    }
    unsigned long generateKey();
    unsigned long getKey() const {return key;}
    int getPageNo() const {return pageNo;}
    int getlineNo() const {return lineNo;}
    int getindex() const {return index;}
    char getC() const {return c;}
    void setC(char c) {this->c=c;}
    // wrting to the file
    friend ostream &operator<<( ostream &output, const BookChar &tempBook ) {
        output << tempBook.pageNo << '\t' << tempBook.lineNo << '\t' << tempBook.index << '\t' << tempBook.c << '\n';
        return output;
    }
    // taking from file
    friend istream &operator>>( istream  &input, BookChar &tempBook ) {
        string pageNo,lineNo,index,c;
        
        if (tempBook.isInsertion) {
            if (getline(input,pageNo,'\t') && getline(input,lineNo,'\t') && getline(input,index,'\t') && getline(input,c,'\n')) {
                tempBook.pageNo = stoi(pageNo);
                tempBook.lineNo = stoi(lineNo);
                tempBook.index = stoi(index);
                tempBook.c = c[0];
                tempBook.key = tempBook.generateKey();
            }
        }else {
            if (getline(input,pageNo,'\t') && getline(input,lineNo,'\t') && getline(input,index,'\n')) {
                tempBook.pageNo = stoi(pageNo);
                tempBook.lineNo = stoi(lineNo);
                tempBook.index = stoi(index);
                tempBook.key = tempBook.generateKey();
            }
        }
        return input;
    }
};

#endif /* p3char_hpp */
