//
//  cookie.cpp
//  homework3
//
//  150140707
//  Muhammet UÇAN
//

#include "cookie.h"
#include <iostream>
//int Cookie::stock = 0;

Cookie::Cookie(string name, int pieces, int price_per_dozen) {
    this->name = name;
    this->pieces = pieces;
    this->price_per_dozen = price_per_dozen;
    cost = pieces * price_per_dozen/12;
}
// since container does not contain pointer, no need to delete something in destructor
Cookie::~Cookie() {
}

ostream& operator<< (ostream& out, const Cookie& cookie) {
    out << cookie.name << " #" << cookie.pieces << " " << cookie.price_per_dozen;
    return out;
}
