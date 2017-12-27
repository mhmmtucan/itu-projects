//
//  candy.cpp
//  homework3
//
//  150140707
//  Muhammet UÇAN
//

#include "candy.h"
#include <iostream>

Candy::Candy(string name, float weight, int price_per_kg) {
    this->name = name;
    this->weight = weight;
    this->price_per_kg = price_per_kg;
    cost = weight * price_per_kg;

}
// since container does not contain pointer, no need to delete something in destructor
Candy::~Candy() {
}

ostream& operator<< (ostream& out, const Candy& candy) {
    out << candy.name << " #" << candy.weight << " " << candy.price_per_kg;
    return out;
}
